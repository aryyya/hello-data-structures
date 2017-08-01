#include "algorithms.hpp"
#include "person.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

struct Options {
  bool print_results = false;
  bool bubble_sort = false;
  bool insertion_sort = false;
};

struct SortMethod {
  std::string name;
  void (*function)(std::vector<Person>&);
  uint64_t runtime = 0;
};

void fatal_error(const std::string& message) {
  std::cerr << message << "\n";
  std::exit(-1);
}

Options parse_options(std::vector<std::string> argv) {
  Options options;
  for (auto& arg : argv) {
    if (arg == "--print-results") options.print_results = true;
    if (arg == "--bubble-sort") options.bubble_sort = true;
    if (arg == "--insertion-sort") options.insertion_sort = true;
  }
  return options;
}

std::vector<SortMethod> load_sort_methods(const Options& options) {
  std::vector<SortMethod> sort_methods;
  if (options.bubble_sort) sort_methods.push_back({ "Bubble Sort", algorithms::bubble_sort });
  if (options.insertion_sort) sort_methods.push_back({ "Insertion Sort", algorithms::insertion_sort });
  return sort_methods;
}

std::vector<Person> load_data(const char *path) {
  std::ifstream file_stream { path };
  if (!file_stream) {
    fatal_error("error: data path '" + (std::string) path + "' could not be opened");
  }
  std::vector<Person> people;
  std::string name;
  uint32_t birth_year;
  while (file_stream.good()) {
    file_stream >> name;
    file_stream >> birth_year;
    people.push_back({ name, birth_year });
  }
  file_stream.close();
  return people;
}

void print_data(const std::vector<Person>& data) {
  for (auto& person : data) {
    std::cout << std::setw(12) << person << " " << std::setw(4) << person.get_age() << "\n";
  }
  std::cout << "\n";
}

void run_sort_methods(std::vector<Person>& data, std::vector<SortMethod>& sort_methods, const bool print_results) {
  for (auto& sort_method : sort_methods) {
    std::cout << "Running '" << sort_method.name << "' on " << data.size() << " element data set: " << std::flush;

    const auto time_start = std::chrono::high_resolution_clock::now();

    sort_method.function(data);

    const auto time_end = std::chrono::high_resolution_clock::now();
    sort_method.runtime = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start).count();

    std::cout << "COMPLETE\n";
    std::cout << "Duration: " << sort_method.runtime << " microseconds (" << (sort_method.runtime / 1000000.0) << " seconds)." << "\n";
    if (print_results) {
      std::cout << "Results:\n";
      print_data(data);
    }
  }
}

int main(int argc, char *argv[]) {

  // parse command-line
  if (argc < 2) {
    fatal_error("error: data path not provided");
  }
  std::vector<std::string> args = { argv, argv + argc };
  const Options options = parse_options(args);

  // load data set
  std::vector<Person> data = load_data(args[1].c_str());
  std::vector<SortMethod> sort_methods = load_sort_methods(options);

  // execute sorts
  run_sort_methods(data, sort_methods, options.print_results);

  return 0;
}

#include "algorithms.hpp"
#include "person.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

struct Options {
  bool help = false;
  bool print_results = false;
  bool aggregate_results = false;
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
    if (arg == "--help") options.help = true;
    if (arg == "--print-results") options.print_results = true;
    if (arg == "--aggregate-results") options.aggregate_results = true;
    if (arg == "--bubble-sort") options.bubble_sort = true;
    if (arg == "--insertion-sort") options.insertion_sort = true;
  }
  return options;
}

void print_help() {
  std::cout << "\n";
  std::cout << "Usage:\n\n";
  std::cout << "  $ ./a.out [data-path] [options]\n";
  std::cout << "\n";
  std::cout << "Options:\n\n";
  std::cout << "  --help               Show help screen and quit.\n";
  std::cout << "  --print-results      Show ordered data after each sort.\n";
  std::cout << "  --aggregate-results  Show runtime chart after all sorts are complete.\n";
  std::cout << "\n";
  std::cout << "  --bubble-sort        Execute the bubble sort algorithm.\n";
  std::cout << "  --insertion-sort     Execute the insertion sort algorithm.\n";
  std::cout << "\n";
  std::cout << "Example:\n\n";
  std::cout << "  $ ./a.out data/mini --bubble-sort --insertion-sort --print-results --aggregate-results\n";
  std::cout << "\n";
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
    fatal_error("Error: data path '" + (std::string) path + "' could not be opened (use --help).");
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
}

void print_aggregate(const std::vector<SortMethod>& sort_methods) {
  std::cout << "\nResults Aggregate:\n\n";
  for (const auto& method : sort_methods) {
    std::cout << std::setw(16) << method.name << ": "
        << std::setw(10) << method.runtime << " µs " 
        << std::setw(10) << (method.runtime / 1e6) << " sec\n";
  }
}

void run_sort_methods(std::vector<Person>& data, std::vector<SortMethod>& sort_methods, const bool print_results) {
  for (auto& sort_method : sort_methods) {
    std::cout << "\nRunning '" << sort_method.name << "' on " << data.size() << " element data set: " << std::flush;
    std::vector<Person> data_copy = data;
    const auto time_start = std::chrono::high_resolution_clock::now();
    sort_method.function(data_copy);
    const auto time_end = std::chrono::high_resolution_clock::now();
    sort_method.runtime = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start).count();

    std::cout << "COMPLETE\n";
    std::cout << "Duration: " << sort_method.runtime << " µs (" << (sort_method.runtime / 1000000.0) << " seconds)." << "\n";
    if (print_results) {
      std::cout << "\nResults:\n\n";
      print_data(data_copy);
    }
  }
}

int main(int argc, char *argv[]) {

  // parse command-line
  if (argc < 2) {
    fatal_error("Error: data path not provided (use --help).");
  }
  std::vector<std::string> args = { argv, argv + argc };
  const Options options = parse_options(args);

  // display help and exit
  if (options.help) {
    print_help();
    return 0;
  }

  // load data set
  std::vector<Person> data = load_data(args[1].c_str());
  std::vector<SortMethod> sort_methods = load_sort_methods(options);

  // execute sorts
  run_sort_methods(data, sort_methods, options.print_results);

  // display output
  if (options.aggregate_results) {
    print_aggregate(sort_methods);
  }
  std::cout << "\n";

  return 0;
}

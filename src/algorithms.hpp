#pragma once

#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

namespace algorithms {

  template <class T>
  std::string print(const T array[], const size_t array_size) {
    std::ostringstream output;
    output << "{ ";
    for (size_t i = 0; i < array_size; i++) {
      output << array[i] << (i < array_size - 1 ? ", " : "");
    }
    output << " }";
    return output.str();
  }

  template <class T>
  std::string print(const std::vector<T>& vector) {
    return algorithms::print(&vector[0], vector.size());
  }

  template <class T>
  void swap(T& x, T& y) {
    const T z = x;
    x = y;
    y = z;
  }

  template <class T>
  void quick_sort(const T array[], const size_t array_size) {
    (void) array;
    (void) array_size; 
  }

  template <class T>
  void bubble_sort(T array[], const size_t array_size) {
    bool sorted = false;
    for (size_t i = 0; !sorted && i < array_size; i++) {
      sorted = true;
      for (size_t j = 0; j < array_size - i - 1; j++) {
        T& this_element = array[j];
        T& next_element = array[j + 1];
        if (this_element > next_element) {
          algorithms::swap(this_element, next_element);
          sorted = false;
        }
      }
    }
  }

  template <class T>
  void bubble_sort(std::vector<T>& vector) {
    bubble_sort(&vector[0], vector.size());
  }

  template <class T>
  void insertion_sort(T array[], const size_t array_size) {
    size_t i = 1;
    while (i < array_size) {
      const T this_element = array[i];
      size_t j = i - 1;
      while (j != SIZE_MAX && array[j] > this_element) {
        array[j + 1] = array[j];
        j--;
      }
      array[j + 1] = this_element;
      i++;
    }
  }

  template <class T>
  void insertion_sort(std::vector<T>& vector) {
    insertion_sort(&vector[0], vector.size());
  }
}

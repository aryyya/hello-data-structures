#pragma once

#include <string>
#include <iostream>
#include <cstdint>

class Person {

private:
  std::string name;
  uint32_t birth_year;

public:
  Person(const std::string name, const uint32_t birth_year) : name(name), birth_year(birth_year) {}

  const std::string& get_name() const {
    return name;
  }

  uint32_t get_age() const {
    return 2017 - birth_year;
  }
};

std::ostream& operator<<(std::ostream& o, const Person& p) {
  return o << p.get_name();
}

bool operator<(const Person& p1, const Person& p2) {
  return p1.get_age() < p2.get_age();
}

bool operator>(const Person& p1, const Person& p2) {
  return p1.get_age() > p2.get_age();
}

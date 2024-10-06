#ifndef BUCLES_H
#define BUCLES_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Bucles {
 public:
  Bucles() = default;
  Bucles(const std::string& bucle, const int& linea) : bucle_{bucle}, linea_{linea} {}
  std::string GetBucle() const { return bucle_; }
  int GetNum() const { return linea_; }
 private:
  std::string bucle_;
  int linea_;
};
std::ostream& operator<<(std::ostream& os, const Bucles& otro);

#endif

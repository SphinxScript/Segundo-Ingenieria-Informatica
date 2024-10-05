#ifndef BUCLES_H
#define BUCLES_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Bucles {
 public:
  Bucles() = default;
  void ProcesarLinea(const std::string& linea, const int& numero);
  std::vector<std::string> GetBucles() const { return bucles_; }
  std::vector<int> GetNum() const { return num_linea_; }
 private:
  std::vector<std::string> bucles_;
  std::vector<int> num_linea_;
};
std::ostream& operator<<(std::ostream& os, const Bucles& otro);

#endif
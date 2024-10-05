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
  
 private:
  std::vector<int> num_linea_;
};
#endif
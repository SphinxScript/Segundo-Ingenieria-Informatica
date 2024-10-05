#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Variables {
 public:
  Variables() = default;    //constructor por defecto
  void ProcesarLinea(const std::string& linea, const int& numero);
  std::vector<std::string> GetVars() const { return variables_; }
  std::vector<int> GetNum() const { return num_linea_; }
 private:
  std::vector<std::string> variables_;
  std::vector<int> num_linea_;
};
std::ostream& operator<<(std::ostream& os, const Variables& otro);

#endif
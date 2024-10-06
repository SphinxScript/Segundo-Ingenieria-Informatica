#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Variables {
 public:
  Variables() = default;    //constructor por defecto
  Variables(const std::string& variable, const int& indice) : variable_{variable}, indice_{indice} {}
  std::string GetVariable() const { return variable_; }
  int GetIndice() const { return indice_; }
 private:
  std::string variable_;
  int indice_;
};
std::ostream& operator<<(std::ostream& os, const Variables& otro);

#endif
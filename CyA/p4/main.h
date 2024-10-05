#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Main {
 public:
  Main() = default;
  void ProcesarLinea(const std::string& linea);
  bool Exist() const { return main_; }
 private:
  bool main_{false};
};
std::ostream& operator<<(std::ostream& os, const Main& imprimir);

#endif
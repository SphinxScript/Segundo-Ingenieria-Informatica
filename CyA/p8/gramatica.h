#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <iostream>
#include <map>

#include "alfabeto.h"

class Gramatica {
 public:
  Gramatica() = default;
  Gramatica(const Alfabeto& alfabeto, const char& arranque, const std::set<char>& simbolos_no_terminales, const std::multimap<std::string, std::string>& producciones)
            : alfabeto_(alfabeto), arranque_(arranque), simbolos_no_terminales_(simbolos_no_terminales), producciones_(producciones) {}
  
  Alfabeto GetAlfabeto() const { return alfabeto_; }
  char GetArranque() const { return arranque_; }
  std::set<char> GetSimbolosNoTerminales() const { return simbolos_no_terminales_; }
  std::multimap<std::string, std::string> GetProducciones() const { return producciones_; }
  
  Gramatica ConvierteCNF(const Gramatica& gramatica) const;
 private:
  Alfabeto alfabeto_;
  char arranque_;
  std::set<char> simbolos_no_terminales_;
  std::multimap<std::string, std::string> producciones_;
};
std::ostream& operator<<(std::ostream& os, const Gramatica& gramatica);

#endif
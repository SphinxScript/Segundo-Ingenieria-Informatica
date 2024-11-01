#include <iostream>

#include "gramatica.h"


std::ostream& operator<<(std::ostream& os, const Gramatica& gramatica) {
  os << "Alfabeto: " << gramatica.GetAlfabeto() << std::endl;
  os << "Simbolos no terminales: ";
  for (const char& simbolo : gramatica.GetSimbolosNoTerminales()) {
    os << simbolo << " ";
  }
  os << std::endl;
  os << "Arranque: " << gramatica.GetArranque() << std::endl;
  os << "Producciones: " << std::endl;
  for (const std::pair<const std::string, std::string>& produccion : gramatica.GetProducciones()) {
    os << produccion.first << " -> " << produccion.second << std::endl;
  }
  return os;
}
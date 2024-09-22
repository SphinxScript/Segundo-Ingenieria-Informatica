#include "alfabeto.h"

Alfabeto::Alfabeto(const std::string& cadena) {
  for (char c : cadena) {
    alfabeto_.insert(c);
  }
}

std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto) {
  int contador{0};
  os << "{";
	for (const char& c : alfabeto.GetAlfabeto()) {
    os << c;
    ++contador;
    if (contador != alfabeto.GetSize()) {
      os << ", ";
    }
  }
  os << "}" << std::endl;
  return os;
}
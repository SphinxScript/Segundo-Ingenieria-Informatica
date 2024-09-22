#include "cadena.h"

Cadena::Cadena(const std::string& cadena) {
  cadena_ = cadena;
}

std::string Cadena::Inversa() const {
  std::string cadena{GetCadena()};
  std::string cadenaInvertida;
  cadenaInvertida.resize(cadena.size());
  int indice{static_cast<int>(cadena.size()) - 1};
  for (int i{0}; i < cadena.size(); ++i) {
    cadenaInvertida[indice] = cadena[i];
    --indice;
  }
  return cadenaInvertida;
}

bool Cadena::operator<(const Cadena& otro) const {
  return cadena_.size() < otro.cadena_.size();
}

std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  std::string cadenita = cadena.GetCadena();
  if (cadenita == "") os << "&";
  os << cadenita;
  return os;
}

void Cadena::Longitud (std::ostream& os) const {
  std::string cadena{GetCadena()};
  os << cadena.size() << std::endl;
}
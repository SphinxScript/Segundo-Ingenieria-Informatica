#include "conjunto.h"


void Conjunto::Insert(const Cadena& cadena) {
  conjunto_.insert(cadena);
}

void Conjunto::ConjuntoPrefijos(const Cadena& cadena) {
  Cadena vacia{""};
  Insert(vacia);
  std::string copiaCadena = cadena.GetCadena();
  for (int i{0}; i <= static_cast<int>(cadena.Size()); ++i) {
    Cadena subcadena;
    std::string prefijo = copiaCadena.substr(0, i);
    subcadena = prefijo;
    Insert(subcadena);
  }
}

void Conjunto::ConjuntoSufijos(const Cadena& cadena) {
  Cadena vacia{""};
  Insert(vacia);
  std::string copiaCadena = cadena.GetCadena();
  int indice{0};
  for (int i{static_cast<int>(copiaCadena.size())}; i >= 0; --i) {
    Cadena subcadena;
    std::string sufijo = copiaCadena.substr(i, indice);
    subcadena = sufijo;
    Insert(subcadena);
    ++indice;
  }
}

std::ostream& operator<<(std::ostream& os, const Conjunto& conjunto) {
  std::set<Cadena> cadenas = conjunto.GetConjunto();
  os << "{";
  int contador{0};
  for (const auto& cadena : cadenas) {
    os << cadena;
    ++contador;
    if (contador != conjunto.Size()) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

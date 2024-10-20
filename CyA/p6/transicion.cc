#include "transicion.h"


#include <iostream>

void Transicion::InsertarEstado(int estado_siguiente) {
  estado_siguiente_.insert(estado_siguiente);
}

std::ostream& operator<<(std::ostream& os, const Transicion& transicion) {
  os << "Símbolo: " << transicion.GetSimbolo() << ", Estados siguientes: { ";
  for (const auto& estado : transicion.GetEstadoSiguiente()) {
    os << estado << " ";
  }
  os << "}";
  return os;
}
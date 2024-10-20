#include "transicion.h"


#include <iostream>

std::ostream& operator<<(std::ostream& os, const Transicion& transicion) {
  os << transicion.GetSimbolo() << " --> " << transicion.GetEstadoSiguiente();
  return os;
}
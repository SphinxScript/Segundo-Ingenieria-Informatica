#include "estado.h"


#include <iostream>
#include <map>

void Estado::InsertTransicion(char simbolo, int estado_siguiente) {
  transiciones_.insert({simbolo, estado_siguiente});
}

std::ostream& operator<<(std::ostream& os, const Estado& estado) {
  os << "Estado: " << estado.GetEstado() << std::endl;
  os << "Aceptacion: " << estado.GetAceptacion() << std::endl;
  os << "Numero de transiciones: " << estado.GetNumeroTransiciones() << std::endl;
  for (const std::pair<const char, int>& transicion : estado.GetTransiciones()) {
    os << "Simbolo: " << transicion.first << " --> " << transicion.second << std::endl;
  }
  return os;
}
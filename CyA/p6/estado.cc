#include "estado.h"


#include <iostream>

std::ostream& operator<<(std::ostream& os, const Estado& estado) {
  os << "Estado: " << estado.GetEstado() << std::endl;
  os << "Aceptacion: " << estado.GetAceptacion() << std::endl;
  os << "Numero de transiciones: " << estado.GetNumeroTransiciones() << std::endl;
  for (const Transicion& transicion : estado.GetTransiciones()) {
    os << transicion << std::endl;
  }
  return os;
}
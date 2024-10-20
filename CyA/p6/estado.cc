#include "estado.h"


#include <iostream>


void Estado::InsertTransicion(Transicion nueva_transicion) {
  // verifico si ya existe una transicion con el mismo simbolo
  for (Transicion& transicion : transiciones_) {
    if (transicion.GetSimbolo() == nueva_transicion.GetSimbolo()) {
      // si existe, agrego el estado siguiente a la transición existente
      for (const int& estado_siguiente : nueva_transicion.GetEstadoSiguiente()) {
        transicion.InsertarEstado(estado_siguiente);
      }
      return;
    }
  }
  // Si no existe, agregar la nueva transición
  transiciones_.push_back(nueva_transicion);
}

std::ostream& operator<<(std::ostream& os, const Estado& estado) {
  os << "Estado: " << estado.GetEstado() << std::endl;
  os << "Aceptacion: " << estado.GetAceptacion() << std::endl;
  os << "Numero de transiciones: " << estado.GetNumeroTransiciones() << std::endl;
  for (const Transicion& transicion : estado.GetTransiciones()) {
    os << transicion << std::endl;
  }
  return os;
}
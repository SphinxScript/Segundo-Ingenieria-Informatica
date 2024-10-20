#ifndef ESTADO_H
#define ESTADO_H

#include <vector>
#include "transicion.h"

class Estado {
 public:
  Estado() = default;
  // implemento de esta forma el el constructor ya que es simple y asi no creo
  // otro archivo de implementacion
  Estado(int estado, int aceptacion, int numero_transiciones) : estado_{estado}, aceptacion_{aceptacion}, numero_transiciones_{numero_transiciones} {}
  void InsertTransicion(Transicion transicion) { transiciones_.push_back(transicion); }
  int GetEstado() const { return estado_; }
  int GetAceptacion() const { return aceptacion_; }
  int GetNumeroTransiciones() const { return numero_transiciones_; }
  std::vector<Transicion> GetTransiciones() const { return transiciones_; }
 private:
  int estado_;
  std::vector<Transicion> transiciones_;
  int aceptacion_;
  int numero_transiciones_;
};
std::ostream& operator<<(std::ostream& os, const Estado& estado);


#endif
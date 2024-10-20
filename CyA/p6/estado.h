#ifndef ESTADO_H
#define ESTADO_H

#include <vector>
#include <set>
#include <map>
#include <iostream>
//#include "transicion.h"

class Estado {
 public:
  Estado() = default;
  // implemento de esta forma el el constructor ya que es simple y asi no creo
  // otro archivo de implementacion
  Estado(int estado, int aceptacion, int numero_transiciones) : estado_{estado}, aceptacion_{aceptacion}, numero_transiciones_{numero_transiciones} {}
  void InsertTransicion(char simbolo, int estado_siguiente);
  int GetEstado() const { return estado_; }
  int GetAceptacion() const { return aceptacion_; }
  int GetNumeroTransiciones() const { return numero_transiciones_; }
  std::multimap<char, int> GetTransiciones() const { return transiciones_; }
  bool operator<(const Estado& estado) const { return estado_ < estado.GetEstado(); }
 private:
  int estado_;
  int aceptacion_;
  int numero_transiciones_;
  std::multimap<char, int> transiciones_;
};
std::ostream& operator<<(std::ostream& os, const Estado& estado);


#endif
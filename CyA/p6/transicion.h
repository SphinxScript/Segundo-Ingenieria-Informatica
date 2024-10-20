#ifndef TRANSICION_H
#define TRANSICION_H

#include <iostream>
#include <set>

class Transicion {
 public:
  Transicion() = default;
  Transicion(char simbolo, int estado_siguiente) : simbolo_{simbolo} {
    estado_siguiente_.insert(estado_siguiente);  // Insertar estado en el conjunto
  }
  void InsertarEstado(int estado_siguiente);
  char GetSimbolo() const { return simbolo_; }
  std::set<int> GetEstadoSiguiente() const { return estado_siguiente_; }
 private:
  char simbolo_;
  std::set<int> estado_siguiente_;
};
std::ostream& operator<<(std::ostream& os, const Transicion& transicion);

#endif
#ifndef TRANSICION_H
#define TRANSICION_H

#include <iostream>

class Transicion {
 public:
  Transicion() = default;
  Transicion(char simbolo, int estado_siguiente) : simbolo_{simbolo}, estado_siguiente_{estado_siguiente} {}
  char GetSimbolo() const { return simbolo_; }
  int GetEstadoSiguiente() const { return estado_siguiente_; }
 private:
  char simbolo_;
  int estado_siguiente_;
};
std::ostream& operator<<(std::ostream& os, const Transicion& transicion);

#endif
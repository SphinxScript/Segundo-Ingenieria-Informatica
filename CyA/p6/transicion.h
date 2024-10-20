#ifndef TRANSICION_H
#define TRANSICION_H

class Transicion {
 public:
  Transicion() = default;
  Transicion(char simbolo, unsigned estado_siguiente) : simbolo_{simbolo}, estado_siguiente_{estado_siguiente} {}
  char GetSimbolo() const { return simbolo_; }
  unsigned GetEstadoSiguiente() const { return estado_siguiente_; }
 private:
  char simbolo_;
  unsigned estado_siguiente_;
};


#endif
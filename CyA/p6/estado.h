#ifndef ESTADO_H
#define ESTADO_H

#include <vector>
#include "transicion.h"

class Estado {
 public:
  Estado() = default;
  // implemento de esta forma el el constructor ya que es simple y asi no creo
  // otro archivo de implementacion
  Estado(unsigned estado, Transicion transicion) : estado_{estado} {
    transiciones_.push_back(transicion);
  }
 private:
  unsigned estado_;
  std::vector<Transicion> transiciones_;
};

#endif
#ifndef DFA_H
#define DFA_H

#include "alfabeto.h"
#include "estado.h"
#include "alfabeto.h"
#include "transicion.h"

#include <set>

class Dfa {
 public:
  Dfa() = default;
  Dfa(const Alfabeto& alfabeto, unsigned numero_estados, unsigned estado_inicial, const std::set<Estado>& estados);
 private:
  Alfabeto alfabeto_;
  unsigned numero_estados_;
  unsigned estado_inicial_;
  std::set<Estado> estados_;
};


#endif
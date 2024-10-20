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
  Dfa(const Alfabeto& alfabeto, int numero_estados, int estado_inicial, const std::set<Estado>& estados);
  Alfabeto GetAlfabeto() const { return alfabeto_; }
  int GetNumeroEstados() const { return numero_estados_; }
  int GetEstadoInicial() const { return estado_inicial_; }
  std::set<Estado> GetEstados() const { return estados_; }
 private:
  Alfabeto alfabeto_;
  int numero_estados_;
  int estado_inicial_;
  std::set<Estado> estados_;
};
std::ostream& operator<<(std::ostream& os, const Dfa& dfa);


#endif
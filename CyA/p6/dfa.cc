#include "dfa.h"


Dfa::Dfa(const Alfabeto& alfabeto, unsigned numero_estados, unsigned estado_inicial, const std::set<Estado>& estados) {
  alfabeto_ = alfabeto;
  numero_estados_ = numero_estados;
  estado_inicial_ = estado_inicial;
  estados_ = estados;
}
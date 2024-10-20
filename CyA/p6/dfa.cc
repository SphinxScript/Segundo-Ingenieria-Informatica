#include "dfa.h"


Dfa::Dfa(const Alfabeto& alfabeto, int numero_estados, int estado_inicial, const std::set<Estado>& estados)
  : alfabeto_{alfabeto}, numero_estados_{numero_estados}, estado_inicial_{estado_inicial}, estados_{estados} {}

std::ostream& operator<<(std::ostream& os, const Dfa& dfa) {
  os << "Alfabeto: " << dfa.GetAlfabeto();
  os << "Numero de estados: " << dfa.GetNumeroEstados() << std::endl;
  os << "Estado inicial: " << dfa.GetEstadoInicial() << std::endl << std::endl;
  for (const Estado& estado : dfa.GetEstados()) {
    os << estado << std::endl;
  }
  return os;
}
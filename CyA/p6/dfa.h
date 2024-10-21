#ifndef DFA_H
#define DFA_H

#include "alfabeto.h"
#include "estado.h"
#include "alfabeto.h"
#include "cadena.h"

#include <set>

class Dfa {
 public:
  Dfa() = default;
  Dfa(const Alfabeto& alfabeto, int numero_estados, int estado_inicial, const std::map<int, Estado>& estados);
  Alfabeto GetAlfabeto() const { return alfabeto_; }
  int GetNumeroEstados() const { return numero_estados_; }
  int GetEstadoInicial() const { return estado_inicial_; }
  std::map<int, Estado> GetEstados() const { return estados_; }
  void ProcesarCadenas(const std::vector<Cadena>& cadenas) const;
 private:
  bool ValidarCadena(const std::string& cadena) const;
  std::set<int> ExplorarEpsilonTransiciones(const std::set<int>& estados) const;
  Alfabeto alfabeto_;
  int numero_estados_;
  int estado_inicial_;
  std::map<int, Estado> estados_;
};
std::ostream& operator<<(std::ostream& os, const Dfa& dfa);


#endif
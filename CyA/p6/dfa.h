// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 17/10/2024
// Archivo: dfa.h
// Contiene la declaración de la clase Dfa
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código


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
  std::set<int> EpsilonClausura(const std::set<int>& estados) const;
  Alfabeto alfabeto_;
  int numero_estados_;
  int estado_inicial_;
  std::map<int, Estado> estados_;
};

std::ostream& operator<<(std::ostream& os, const Dfa& dfa);


#endif
// Universidad de La Laguna
// Escuela Superior de Ingenier´ıa y Tecnolog´ıa
// Grado en Ingenier´ıa Inform´atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la funci´on main del proyecto que usa las clases X e Y
// para ... (indicar brevemente el objetivo)
// Referencias:
// Enlaces de inter´es

// Historial de revisiones
// 17/09/2024 - Creaci´on (primera versi´on) del c´odigo

#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <set>
#include <iostream>
#include <string>

#include "cadena.h"

class Conjunto {
 public:
  Conjunto() {};
  std::set<Cadena> GetConjunto() const { return conjunto_; }
  void Insert(const Cadena&);
  int Size() const { return conjunto_.size(); }
  void ConjuntoPrefijos(const Cadena& cadena);
  void ConjuntoSufijos(const Cadena& cadena);
 private:
  std::set<Cadena> conjunto_;
};
std::ostream& operator<<(std::ostream& os, const Conjunto& conjunto);


#endif
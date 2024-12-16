// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: conjunto.h
// Contiene la definición de la clase conjunto
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <set>
#include <iostream>
#include <string>

#include "cadena.h"

class Conjunto {
 public:
  Conjunto() = default;
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
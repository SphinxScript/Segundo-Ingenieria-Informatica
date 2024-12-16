// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: lenguaje.h
// Contiene la definición de la clase Lenguaje
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#ifndef LENGUAJE_H
#define LENGUAJE_H

#include <set>
#include <iostream>
#include <string>

#include "cadena.h"

class Lenguaje {
 public:
  Lenguaje() = default;
  std::set<Cadena> GetLenguaje() const { return Lenguaje_; }
  void Insert(const Cadena&);
  int Size() const { return Lenguaje_.size(); }
  void LenguajePrefijos(const Cadena& cadena);
  void LenguajeSufijos(const Cadena& cadena);
 private:
  std::set<Cadena> Lenguaje_;
};
std::ostream& operator<<(std::ostream& os, const Lenguaje& Lenguaje);


#endif
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: alfabeto.h
// Contiene la definición de la clase alfabeto
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#ifndef ALFABETO_H
#define ALFABETO_H

#include <set>
#include <iostream>
#include <string>


class Alfabeto {
 public:
  Alfabeto() = default;
  Alfabeto(const std::string& cadena);
  std::set<char> GetAlfabeto() const { return alfabeto_; }
  int GetSize() const { return alfabeto_.size(); }
 private:
  std::set<char> alfabeto_;
};
std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);


#endif
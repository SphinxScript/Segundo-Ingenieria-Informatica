// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en c++
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 04/10/2024
// Archivo: bucles.h
// Contiene la definición de la clase Bucles.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 04/10/2024 - Creación (primera versión) del código

#ifndef BUCLES_H
#define BUCLES_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Bucles {
 public:
  Bucles() = default;
  Bucles(const std::string& bucle, const int& linea) : bucle_{bucle}, linea_{linea} {}
  std::string GetBucle() const { return bucle_; }
  int GetNum() const { return linea_; }
 private:
  std::string bucle_;
  int linea_;
};
std::ostream& operator<<(std::ostream& os, const Bucles& otro);

#endif

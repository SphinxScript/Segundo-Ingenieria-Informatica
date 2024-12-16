// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en c++
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 04/10/2024
// Archivo: variables.h
// Contiene la definición de la clase Variables.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 04/10/2024 - Creación (primera versión) del código

#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Variables {
 public:
  Variables() = default;    //constructor por defecto
  Variables(const std::string& variable, const int& indice) : variable_{variable}, indice_{indice} {}
  std::string GetVariable() const { return variable_; }
  int GetIndice() const { return indice_; }
 private:
  std::string variable_;
  int indice_;
};
std::ostream& operator<<(std::ostream& os, const Variables& otro);

#endif
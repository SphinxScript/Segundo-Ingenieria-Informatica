// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en c++
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 04/10/2024
// Archivo: variables.cc
// Contiene la implementación de los métodos de la clase Variables.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 04/10/2024 - Creación (primera versión) del código

#include "variables.h"


std::ostream& operator<<(std::ostream& os, const Variables& otro) {
  os << "[Line " << otro.GetIndice() << "] " << otro.GetVariable() << std::endl;
  return os;
}
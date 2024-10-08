// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en c++
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 04/10/2024
// Archivo: comentarios_linea.h
// Contiene la definición de la clase ComentariosLinea.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 04/10/2024 - Creación (primera versión) del código

#ifndef COMENTARIOS_LINEA_H
#define COMENTARIOS_LINEA_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class ComentariosLinea {
 public:
  ComentariosLinea() = default;
  ComentariosLinea(const std::string& linea, const int& indice) : linea_{linea}, indice_{indice} {};
  std::string GetLinea() const { return linea_; }
  int GetIndice() const { return indice_; }
 private:
  std::string linea_;
  int indice_;
};
std::ostream& operator<<(std::ostream& os, const ComentariosLinea& otro);

#endif
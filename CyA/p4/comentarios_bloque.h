// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en c++
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 04/10/2024
// Archivo: comentarios_bloque.h
// Contiene la definición de la clase ComentariosBloque.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 04/10/2024 - Creación (primera versión) del código

#ifndef COMENTARIOS_BLOQUE_H
#define COMENTARIOS_BLOQUE_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class ComentariosBloque {
 public:
  ComentariosBloque() = default;
  void ProcesarLinea(const std::string& linea, const int& numero, const int& fin_bloque);
  void PrintIntervalo(std::ostream& os) const;
  std::vector<std::string> GetBloque() const { return comentarios_bloque_; }
  std::vector<int> GetIndices() const { return indices_; }
  bool GetInicio() const { return inicio_bloque_; }
 private:
  bool inicio_bloque_{false};
  std::vector<std::string> comentarios_bloque_;
  std::vector<int> indices_;
};
std::ostream& operator<<(std::ostream& os, const ComentariosBloque& otro);



#endif
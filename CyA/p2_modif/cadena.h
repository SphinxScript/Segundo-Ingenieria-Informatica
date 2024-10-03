// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: cadena.h
// Contiene la definición de la clase cadena
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#ifndef CADENA_H
#define CADENA_H


#include <set>
#include <iostream>
#include <string>

class Cadena {
 public:
  Cadena() = default;
  Cadena(const std::string& cadena);
  std::string GetCadena() const { return cadena_; }
  void ImprimeLongitud(std::ostream& os) const;
  Cadena Inversa() const;
  int Size() const { return cadena_.size(); }
  bool operator<(const Cadena& otro) const;
  void IgualInversa(std::ostream& os) const;
  bool operator==(const Cadena& otro) const;
 private:
  std::string cadena_;
};
std::ostream& operator<<(std::ostream& os, const Cadena& cadena);

#endif
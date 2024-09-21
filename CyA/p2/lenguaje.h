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


#ifndef LENGUAJE_H
#define LENGUAJE_H

#include <set>
#include <iostream>

class Alfabeto {
 public:
  Alfabeto(const std::string& cadena);

  std::set<char> GetAlfabeto() const { return alfabeto_; }

  int GetSize() const { return alfabeto_.size(); }

 private:
  std::set<char> alfabeto_;
};

std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);

class Cadena {
 public:
  Cadena(const std::string& cadena);
  std::string GetCadena() const { return cadena_; }
  void Longitud(std::ostream& os) const;
  std::string Inversa() const;
  std::set<std::string> Prefijos() const;
  std::set<std::string> Sufijos() const;
  void Imprimir(std::ostream& os) const;

 private:
  std::string cadena_;
};
std::ostream& operator<<(std::ostream& os, const Cadena& cadena);
#endif
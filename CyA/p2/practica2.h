// Universidad de La Laguna
// Escuela Superior de Ingenier´ıa y Tecnolog´ıa
// Grado en Ingenier´ıa Inform´atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: aluXXXXX@ull.edu.es
// Fecha: 17/09/2024
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la funci´on main del proyecto que usa las clases X e Y
// para ... (indicar brevemente el objetivo)
// Referencias:
// Enlaces de inter´es

// Historial de revisiones
// 17/09/2024 - Creaci´on (primera versi´on) del c´odigo


#ifndef PRACTICA2_H
#define PRACTICA2_H

#include <set>

class Alfabeto {
 public:
  Alfabeto() {};

  void ImprimeAlfabeto(alfabeto);
  void Longitud(alfabeto);
  void Inversa(alfabeto);
  void Prefijos(alfabeto);
  void Sufijos(alfabeto);

 private:
  std::set<char> alfabeto_;

};

class Cadena : Alfabeto {
 public:
  
 private:
  Alfabeto alfabeto;
};

#endif
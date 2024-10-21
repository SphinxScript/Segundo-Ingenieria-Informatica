// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 17/10/2024
// Archivo: estado.cc
// Contiene la implementacin de los metodos de la clase estado
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#include "estado.h"


#include <iostream>
#include <map>

/**
 * @brief Inserta una transicion en el estado
 * @param simbolo Simbolo de la transicion
 * @param estado_siguiente Estado al que se transita
 * @return void
 */
void Estado::InsertTransicion(char simbolo, int estado_siguiente) {
  transiciones_.insert({simbolo, estado_siguiente});
}

/**
 * @brief Sobrecarga del operador de insercion para la clase Estado
 * @param os Flujo de salida
 * @param estado Estado a imprimir
 * @return Flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const Estado& estado) {
  os << "Estado: " << estado.GetEstado() << std::endl;
  os << "Aceptacion: " << estado.GetAceptacion() << std::endl;
  os << "Numero de transiciones: " << estado.GetNumeroTransiciones() << std::endl;
  for (const std::pair<const char, int>& transicion : estado.GetTransiciones()) {
    os << "Simbolo: " << transicion.first << " --> " << transicion.second << std::endl;
  }
  return os;
}
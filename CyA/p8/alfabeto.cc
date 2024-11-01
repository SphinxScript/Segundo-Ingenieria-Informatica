// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 17/10/2024
// Archivo: alfabeto.cc
// Contiene la implementación de los métodos de la clase alfabeto
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#include "alfabeto.h"

/**
 * @brief: constructor de la clase alfabeto
 * @param[in] os: el output
 * @param[in] cadena: la cadena que se pasa a partir de la cual se construye el alfabeto
 */
Alfabeto::Alfabeto(const std::string& cadena) {
  for (char c : cadena) {
    if (c == ' ') {
      continue;
    }
    else {
      alfabeto_.insert(c);
    }
  }
}

/**
 * @brief: funcion que comprueba si un simbolo pertenece al alfabeto
 * @param caracter: el simbolo que se va a comprobar
 * @return: true si el simbolo pertenece al alfabeto, false en caso contrario
 */
bool Alfabeto::CheckSymbol(const char& caracter) const {
  bool forma_parte{false};
  for (const char& c : GetAlfabeto()) {
    if (c == caracter || caracter == '&') {
      forma_parte = true;
    }
  }
  return forma_parte;
}

/**
 * @brief: funcion que inserta un nuevo caracter en el alfabeto
 * @param caracter: el simbolo que se va a insertar
 * @return: void
 */
void Alfabeto::AddSymbol(const char& caracter) {
  alfabeto_.insert(caracter);
}


/**
 *@brief: la sobrecarga del operador de insercion para la clase Alfabeto
 *@param[in] os: el output
 *@param[in] alfabeto: el alfabeto que se va a imprimir
 *@return: os con el alfabeto impreso
 */

std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto) {
  int contador{0};
  os << "{";
	for (const char& c : alfabeto.GetAlfabeto()) {
    os << c;
    ++contador;
    if (contador != alfabeto.GetSize()) {
      os << ", ";
    }
  }
  os << "}" << std::endl;
  return os;
}
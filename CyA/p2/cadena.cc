// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: cadena.cc
// Contiene la implementación de los métodos de la clase cadena
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#include "cadena.h"


/**
 * @brief constructor de la clase Cadena
 * @param cadena una string que se le pasa al constructor a partir de la cual se crea el objeto.
 */

Cadena::Cadena(const std::string& cadena) {
  cadena_ = cadena;
}

/**
 * @brief metodo que hace la inversa de la cadena que invoca el metodo
 * @return cadenaInvertida retorna la cadena invertida.
 */
std::string Cadena::Inversa() const {
  std::string cadena{GetCadena()};
  std::string cadenaInvertida;
  cadenaInvertida.resize(cadena.size());
  int indice{static_cast<int>(cadena.size()) - 1};
  for (int i{0}; i < cadena.size(); ++i) {
    cadenaInvertida[indice] = cadena[i];
    --indice;
  }
  return cadenaInvertida;
}

/**
 * @brief sobrecarga del operador "<"
 * @param model, plate, kilometers el que emplea parametros lleva sus parametros correspondientes para crear el objeto coche.
 * @return no retornan nada, ya que son constructores.
 */
bool Cadena::operator<(const Cadena& otro) const {
  return cadena_.size() < otro.cadena_.size();
}

std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  std::string cadenita = cadena.GetCadena();
  if (cadenita == "") os << "&";
  os << cadenita;
  return os;
}

void Cadena::Longitud (std::ostream& os) const {
  std::string cadena{GetCadena()};
  os << cadena.size() << std::endl;
}
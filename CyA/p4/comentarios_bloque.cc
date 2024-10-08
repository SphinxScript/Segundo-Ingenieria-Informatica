// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en c++
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 04/10/2024
// Archivo: comentarios_bloque.cc
// Contiene la implementación de los métodos de la clase ComentariosBloque.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 04/10/2024 - Creación (primera versión) del código

#include "comentarios_bloque.h"


void ComentariosBloque::ProcesarLinea(const std::string& linea, const int& numero, const int& fin_bloque) {
  std::regex inicio_bloque{"\\/\\*"};
  std::regex final_bloque{"\\*\\/"};
  if (!inicio_bloque_) {
    std::smatch coincidencias;
    if (std::regex_search(linea, coincidencias, inicio_bloque)){
      inicio_bloque_ = true;
      comentarios_bloque_.push_back(coincidencias.str());
      indices_.push_back(numero);
    }
  }
  else {
    std::smatch coincidencias;
    if (std::regex_search(linea, coincidencias, final_bloque)) {
      inicio_bloque_ = false;
      comentarios_bloque_.push_back(coincidencias.str());
      indices_.push_back(fin_bloque);
    }
    else {
    comentarios_bloque_.push_back(linea);
    }
  }
}

void ComentariosBloque::PrintIntervalo(std::ostream& os) const {
  std::vector<int> indices{GetIndices()};
  os << "[Line " << indices[0] << "-" << indices[1] << "]";
}

std::ostream& operator<<(std::ostream& os, const ComentariosBloque& otro) {
  std::vector<std::string> vector{otro.GetBloque()};
  for (int i{0}; i < static_cast<int>(vector.size()); ++i) {
    os << vector[i] << std::endl;
  }
  os << std::endl;
  return os;
}

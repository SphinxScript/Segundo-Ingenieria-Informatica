/**
 * @file point_types.cc
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 07/12/2024
 * @brief Contiene la implementación de los métodos de los operadores de inserción y extracción de flujo para los tipos de datos Point y PointVector
 * @version 1.0
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
 * 
 * @note
 * - 01/11/2024: Creación (primera versión) del código
 */

#include <iomanip>

#include "point_types.h"

std::ostream& operator<<(std::ostream& os, const cya::PointVector& points) {
  os << points.size() << std::endl;

  for (const cya::Point& point : points) {
    os << point << std::endl;
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const cya::Point& point) {
  os << std::setw(kMaxSize) << std::fixed << std::setprecision(kMaxPrecision)
     << point.first << ", "
     << std::setw(kMaxSize) << std::fixed << std::setprecision(kMaxPrecision)
     << point.second;

  return os;
}

std::istream& operator>>(std::istream& is, cya::PointVector& points) {
  int count;
  is >> count;

  points.clear();

  for (int i = 0; i < count; ++i) {
    cya::Point point;
    is >> point;

    points.push_back(point);
  }

  return is;
}

std::istream& operator>>(std::istream& is, cya::Point& point) {
  is >> point.first >> point.second;

  return is;
}

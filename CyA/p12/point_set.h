/**
 * @file point_set.h
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 14/12/2024
 * @brief Contiene la definicion de la clase point_set y los tipos de datos point, line, point_vector y line_vector
 * @version 1.0
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 12: Algoritmos Divide y Vencerás (Divide & Conquer). Cálculo de la envoltura convexa
 * 
 * @note
 * - 01/11/2024: Creación (primera versión) del código
 */

#ifndef POINT_SET_H
#define POINT_SET_H

#include <iostream>
#include <vector>
#include <algorithm>  // Para std::sort y std::unique
#include <cmath>      // Para std::abs

namespace cya {

typedef std::pair<double, double> point;
typedef std::pair<point, point> line;
typedef std::vector<point> point_vector;
typedef std::vector<line> line_vector;

enum side {
  LEFT = -1,
  CENTER = 0,
  RIGHT = 1
};

class point_set : public point_vector {
 private:
  point_vector hull_;
  line_vector lines_; // se usara para imprimir el grafo en opcion -d

 public:
  // Constructor y destructor
  point_set(const std::vector<point>& points) : point_vector(points), hull_{} {} 
  ~point_set() = default;

  // Métodos públicos
  void quickHullPublic(void);                                                     // implementado

  void write_hull(std::ostream& os) const;
  void write_dot(std::ostream& os) const;

  inline const point_vector& get_hull(void) const { return hull_; }
  inline const point_vector& get_points(void) const { return *this; }

 private:
  // Métodos privados
  void quickHull(const line& l, int side);                                  // implementado

  double distance(const line& l, const point& p) const;                     // implementado
  int find_side(const line& l, const point& p) const;                       
  void x_bounds(point& min_x, point& max_x) const;                          // implementado
  double point_2_line(const line& l, const point& p) const;                 // implementado
  bool farthest_point(const line& l, int side, point& farthest) const;      // implementado
};

}  // namespace CyA

#endif  // POINT_SET_H

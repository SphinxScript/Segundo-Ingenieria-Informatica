/**
 * @file point_types.h
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 07/12/2024
 * @brief Contiene la definición del espacio de nombres cya y los tipos de datos Point, PointVector, Arc, WeightedArc, ArcVector, PointCollection y Tree
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

#ifndef Point_TYPES_H
#define Point_TYPES_H

#include <iostream>
#include <utility>
#include <vector>
#include <set>

#define kMaxSize 3
#define kMaxPrecision 0

namespace cya {

typedef std::pair<double, double> Point;

typedef std::vector<Point> PointVector;

typedef std::pair<Point, Point> Arc;
typedef std::pair<double, Arc> WeightedArc;
typedef std::vector<WeightedArc> ArcVector;

typedef std::set<Point> PointCollection;

typedef std::vector<Arc> Tree;

}  // namespace cya

std::ostream& operator<<(std::ostream& os, const cya::PointVector& Points);
std::ostream& operator<<(std::ostream& os, const cya::Point& Point);

std::istream& operator>>(std::istream& is, cya::PointVector& Points);
std::istream& operator>>(std::istream& is, cya::Point& Point);


#endif // Point_TYPES_H
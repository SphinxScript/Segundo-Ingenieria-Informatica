/**
 * @file sub_tree.cc
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 07/12/2024
 * @brief Contiene la implementación de los métodos de la clase SubTree
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
#include <cmath>

#include <algorithm>
#include <utility>
#include <iostream>

#include "sub_tree.h"
#include "point_types.h"


namespace emst {

SubTree::SubTree() : arcs_(), points_(), cost_(0) {}

SubTree::~SubTree() {}

void SubTree::AddArc(const cya::Arc& arc) {
  arcs_.push_back(arc);

  points_.insert(arc.first);
  points_.insert(arc.second);
}

void SubTree::AddPoint(const cya::Point& point) {
  points_.insert(point);
}

bool SubTree::Contains(const cya::Point& point) const {
  return points_.find(point) != points_.end();
}

void SubTree::Merge(const SubTree& subtree, const cya::WeightedArc& arc) {
  arcs_.insert(arcs_.end(), subtree.arcs_.begin(), subtree.arcs_.end());
  arcs_.push_back(arc.second);

  points_.insert(subtree.points_.begin(), subtree.points_.end());

  cost_ += arc.first + subtree.GetCost();
}

std::ostream& operator<<(std::ostream& os, const SubTree& subtree) {
  os << std::fixed << std::setprecision(2) << subtree.GetCost() << std::endl;
  for (const auto& point : subtree.GetPoints()) {
    os << point.first << " " << point.second << std::endl;
  }
  return os;
}

}  // namespace emst
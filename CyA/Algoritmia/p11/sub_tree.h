/**
 * @file sub_tree.h
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 07/12/2024
 * @brief Contiene la definición de la clase SubTree
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

#ifndef SUB_TREE_H
#define SUB_TREE_H

#include <iostream>
#include <cmath>

#include "point_types.h"

namespace emst {

class SubTree {
 public:
  SubTree();
  ~SubTree();

  void AddArc(const cya::Arc& arc);
  void AddPoint(const cya::Point& point);
  bool Contains(const cya::Point& point) const;
  void Merge(const SubTree& subtree, const cya::WeightedArc& arc);

  inline const cya::Tree& GetArcs() const { return arcs_; }
  inline const cya::PointCollection& GetPoints() const { return points_; }
  inline double GetCost() const { return cost_; }

  bool operator<(const SubTree& other) const {
    return cost_ < other.cost_;
  }

 private:
  cya::Tree arcs_;
  cya::PointCollection points_;
  double cost_;
};
std::ostream& operator<<(std::ostream& os, const SubTree& subtree);

using SubTreeVector = std::vector<SubTree>;

}  // namespace emst

#endif // SUB_TREE_H
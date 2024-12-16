/**
 * @file forest.h
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

#ifndef FOREST_H
#define FOREST_H

#include <iostream>

#include "point_types.h"
#include "sub_tree.h"

using Forest = std::vector<emst::SubTree>;

class PointSet : public cya::PointVector {
 public:
  explicit PointSet(const cya::PointVector& points) : cya::PointVector{points}, emst_{} {};
  ~PointSet() = default;

  void ComputeEMST();   // implementado

  void WriteTree(std::ostream& os) const;
  void Write(std::ostream& os) const;

  inline const cya::Tree& GetTree() const { return emst_; }
  inline const cya::PointVector& GetPoints() const { return *this; }
  inline double GetCost() const { return ComputeCost(); }

  void PrintDot(std::ostream& os) const;
  // modificación
  std::vector<cya::Tree> ComputeMultistart(const std::vector<cya::Point>& puntos);

 private:
  cya::Tree emst_;
  void ComputeArcVector(cya::ArcVector& arc_vector) const;    // implementado
  void FindIncidentSubtrees(const Forest& subtrees, const cya::Arc& arc, int& i, int& j) const;
  void MergeSubtrees(Forest& subtrees, const cya::Arc& arc, int i, int j) const;

  double ComputeCost() const;

  double EuclideanDistance(const cya::Arc& arc) const;      // implementado

  // este metodo se usa para devolver el arbol emst a partir de la arista qeu se le pasa
  cya::Tree ReturnEMST(const cya::WeightedArc& arco_inicial);
};

#endif // FOREST_H
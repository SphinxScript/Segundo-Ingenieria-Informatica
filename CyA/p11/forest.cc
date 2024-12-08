/**
 * @file forest.cc
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

#include <algorithm>
#include <iomanip>

#include "forest.h"

void PointSet::ComputeEMST() {    
  cya::ArcVector arc_vector;
  ComputeArcVector(arc_vector);

  Forest subtrees;

  // Inicializa un subárbol para cada punto.
  for (const cya::Point& point : *this) {
    emst::SubTree subtree;
    subtree.AddPoint(point);

    subtrees.push_back(subtree);
  }

  // Construye el EMST usando los arcos ponderados.
  for (const cya::WeightedArc& weighted_arc : arc_vector) {
    int subtree_indice_i, subtree_indice_j;
    FindIncidentSubtrees(subtrees, weighted_arc.second, subtree_indice_i, subtree_indice_j);

    if (subtree_indice_i != subtree_indice_j) {
      MergeSubtrees(subtrees, weighted_arc.second, subtree_indice_i, subtree_indice_j);
    }
  }

  emst_ = subtrees[0].GetArcs();
}

void PointSet::ComputeArcVector(cya::ArcVector& arc_vector) const {   
  arc_vector.clear();

  const int num_points = static_cast<int>(size());

  // Genera todos los arcos posibles con sus respectivas distancias.
  for (int i = 0; i < num_points - 1; ++i) {
    const cya::Point& point_i = (*this)[static_cast<size_t>(i)];

    for (int j = i + 1; j < num_points; ++j) {
      const cya::Point& point_j = (*this)[static_cast<size_t>(j)];

      double distance = EuclideanDistance(std::make_pair(point_i, point_j));

      arc_vector.push_back(std::make_pair(distance, std::make_pair(point_i, point_j)));
    }
  }

  // Ordena los arcos por distancia.
  std::sort(arc_vector.begin(), arc_vector.end());
}

double PointSet::EuclideanDistance(const cya::Arc& arc) const {      
  cya::Point point_i = arc.first;
  cya::Point point_j = arc.second;

  double dx = point_i.first - point_j.first;
  double dy = point_i.second - point_j.second;

  return std::sqrt(dx * dx + dy * dy);
}

void PointSet::FindIncidentSubtrees(const Forest& subtrees, const cya::Arc& arc, int& i, int& j) const {
  i = -1;  // Inicializamos índices a valores no válidos
  j = -1;

  // Iterar sobre el bosque para encontrar los subárboles incidentes al arco
  for (size_t indice = 0; indice < subtrees.size(); ++indice) {
    const auto& subtree = subtrees[indice];

    // Verificar si el subárbol contiene alguno de los extremos del arco
    if (subtree.Contains(arc.first) || subtree.Contains(arc.second)) {
      if (i == -1) {
        i = static_cast<int>(indice);  // Primer subárbol encontrado
      }
      else {
        j = static_cast<int>(indice);  // Segundo subárbol encontrado
        break;      // Ya no necesitamos seguir buscando
      }
    }
  }
}


void PointSet::MergeSubtrees(Forest& subtrees, const cya::Arc& arc, int i, int j) const {
  // Asegurarse de que los índices son válidos
  // Fusionar los subárboles
  if (i >= 0 && j >= 0) {
    cya::WeightedArc weighted_arc;  // Crear un arco ponderado
    weighted_arc.first = EuclideanDistance(arc);  // La distancia entre los extremos del arco
    weighted_arc.second = arc;

    // Combinar el subárbol j en el subárbol i
    subtrees[static_cast<size_t>(i)].Merge(subtrees[static_cast<size_t>(j)], weighted_arc);

    // Eliminar el subárbol j del bosque
    subtrees.erase(subtrees.begin() + j);
  }
}


double PointSet::ComputeCost() const {
  double cost = 0.0;
  for (const auto& arc : emst_) {
    cost += EuclideanDistance(arc);
  }
  return cost;
}

void PointSet::WriteTree(std::ostream& os) const {
  for (const auto& arc : emst_) {
    os << "(" << arc.first << ") -> (" << arc.second << ")" << std::endl;
  }
  os << std::endl;
  os << "Coste total: " << std::setprecision(kMaxPrecision) << ComputeCost() << std::endl;
}
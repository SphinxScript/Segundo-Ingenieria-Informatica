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

void PointSet::PrintDot(std::ostream& os) const {
  os << "graph {" << std::endl << std::endl;
  // creo un set de puntos para no repetirlos y tener todos
  std::set<cya::Point> printed_points;
  for (const auto& arc : emst_) {
    printed_points.insert(arc.first);
    printed_points.insert(arc.second);
  }
  int contador{0};
  // creo un vector de puntos para poder acceder a ellos por índice
  std::vector<cya::Point> printed_points_vector;
  for (const auto& point : printed_points) {
    os << " " << contador << " [pos = \" " << point << "!\"]" << std::endl;
    printed_points_vector.push_back(point);
    ++contador;
  }
  os << std::endl;
  contador = 0;
  // comienzo a iterar, para saber qué punto va a qué punto e imprimirlo acorde al formato de salida esperado
  for (int i{0}; i < static_cast<int>(emst_.size()); ++i) {     // recorremos todas las aristas del árbol
    // creamos dos puntos para poder compararlos con los puntos del vector
    cya::Point point = emst_[static_cast<size_t>(i)].first;
    cya::Point point2 = emst_[static_cast<size_t>(i)].second;
    // recorremos todo el vector de puntos
    for (int j{0}; j < static_cast<int>(printed_points_vector.size()); ++j) {
      // si el punto 1 es igual al punto del vector, guardamos el índice en contador y seguimos buscando el punto de destino (punto2)
      if (point == printed_points_vector[static_cast<size_t>(j)]) {
        contador = j;
        // recorremos de nuevo todo el vector de puntos
        for (int k{0}; k < static_cast<int>(printed_points_vector.size()); ++k) {
          // cuando el punto2 es igual al punto del vector, imprimimos la arista con el formato: x -- y
          // siendo x el indice del punto origen, e y el indice del punto destino, correspondiendose en este bucle
          // a las variables contador y k del bucle actual
          if (point2 == printed_points_vector[static_cast<size_t>(k)]) {
            os << " " << contador << " -- " << k << std::endl;
          }
        }
      }
    }
  }
  os << "}" << std::endl;
}


// MODIFICACIÓN (no funciona)

// std::vector<cya::Tree> PointSet::ComputeMultistart(const std::vector<cya::Point>& puntos) {
//   std::vector<int> indices_aleatorios;
//   for (int i{0}; i < 6; ++i) {
//     int numero = rand() % static_cast<int>(puntos.size());
//     indices_aleatorios.push_back(numero);
//   }
//   std::vector<cya::Arc> arcos;
//   for (int i{0}; i < static_cast<int>(indices_aleatorios.size()); i += 2) {
//     cya::Arc pair = std::make_pair(puntos[static_cast<size_t>(i)], puntos[static_cast<size_t>(i) + 1]);
//     arcos.push_back(pair);  
//   }
//   // para comprobar si esta correcta la creación de las 3 aristas aleatorias
//   // for (const auto& arc : arcos) {
//   //   std::cout << arc.first << " --> " << arc.second << std::endl;
//   // }

//   cya::ArcVector vector_arcos_aleatorios;
//   for (int i{0}; i < static_cast<int>(arcos.size()); ++i) {
//     cya::Arc arco = arcos[i];
//     double peso = EuclideanDistance(arco);
//     cya::WeightedArc arco_ponderado;
//     arco_ponderado = std::make_pair(peso, arco);
//     vector_arcos_aleatorios.push_back(arco_ponderado);
//   }

//   // hasta este punto he logrado crear los 3 arcos aleatorios y sus peso, los weightedArc.

//   // creo un vector
//   std::vector<cya::Tree> vector_de_arboles;

//   for (int i{0}; i < vector_arcos_aleatorios.size(); ++i) {
//     cya::Tree sub_arbol = ReturnEMST(vector_arcos_aleatorios[i]);
//     vector_de_arboles.push_back(sub_arbol);
//   }
//   // devuelvo el conjunto de arboles hallado
//   return vector_de_arboles;
// }

// esta función halla el arbol emst a partir de la arista pasada
// cya::Tree PointSet::ReturnEMST(const cya::WeightedArc& arco_inicial) {    
//   cya::ArcVector arc_vector;
//   ComputeArcVector(arc_vector);

//   arc_vector[0] = arco_inicial;

//   Forest subtrees;

//   // Inicializa un subárbol para cada punto.
//   for (const cya::Point& point : *this) {
//     emst::SubTree subtree;
//     subtree.AddPoint(point);

//     subtrees.push_back(subtree);
//   }

//   // Construye el EMST usando los arcos ponderados.
//   for (const cya::WeightedArc& weighted_arc : arc_vector) {
//     int subtree_indice_i, subtree_indice_j;
//     FindIncidentSubtrees(subtrees, weighted_arc.second, subtree_indice_i, subtree_indice_j);

//     if (subtree_indice_i != subtree_indice_j) {
//       MergeSubtrees(subtrees, weighted_arc.second, subtree_indice_i, subtree_indice_j);
//     }
//   }

//   emst_ = subtrees[0].GetArcs();
// }
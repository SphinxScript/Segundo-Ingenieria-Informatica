/**
 * @file emst_cliente.cc
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 07/12/2024
 * @brief Contiene la implementación del programa cliente y la función usage()
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

#include <iostream>
#include <fstream>
#include <set>

#include "point_types.h"
#include "sub_tree.h"
#include "forest.h"

// pondré el código de usage aquí porque es la única función que se usará como apoyo al main
bool usage(const int& argc) {
  bool usage = false;
  if (argc != 2 && argc != 3) {
    std::cerr << "Error: Número de argumentos incorrecto." << std::endl;
    std::cerr << "Uso: ./emst_cliente <fichero_entrada> [-d]" << std::endl;
    usage = true;
  }
  return usage;
}

int main(int argc, char* argv[]) {
  system("clear");
  if (usage(argc)) return 1;
  std::string filename = argv[1];
  std::ifstream file(filename);
  std::string linea;
  std::getline(file, linea);
  int num_points = std::stoi(linea);
  Forest subtrees;
  std::vector<cya::Point> points;
  for (int i = 0; i < num_points; i++) {
    cya::Point point;
    emst::SubTree subtree;
    file >> point;
    subtree.AddPoint(point);
    subtrees.push_back(subtree);
    points.push_back(point);
  }
  PointSet objeto_emst(points);
  objeto_emst.ComputeEMST();
  objeto_emst.WriteTree(std::cout);
  if (argc == 3) {
    std::string option = argv[2];
    if (option == "-d") {
      std::ofstream output_file("archivo.dot");
      objeto_emst.PrintDot(output_file);
    }
    else {
      std::cerr << "Error: Opción incorrecta." << std::endl;
      std::cerr << "Uso: ./tree_emst.out <fichero_entrada> [-d]" << std::endl;
      return EXIT_FAILURE;
    }
  }


  // modificacion
  // std::cout << "Modificación" << std::endl;
  // std::vector<cya::Tree> arboles = objeto_emst.ComputeMultistart(points);
  // for (const auto& arbol : arboles) {
  //   //std::cout << arbol << std::endl;
  // }
  return EXIT_SUCCESS;
}
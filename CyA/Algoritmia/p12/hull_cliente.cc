/**
 * @file hull_cliente.cc
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 14/12/2024
 * @brief Contiene la implementación del programa cliente y la función usage()
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

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "point_set.h"

/**
 * @brief: función que comprueba si el número de argumentos es correcto
 * @param[in] argc: número de argumentos
 * @return bool: devuelve true si el número de argumentos es incorrecto
 */
bool usage(const int& argc) {
  bool usage = false;
  if (argc != 2 && argc != 3) {
    std::cerr << "Error: Número de argumentos incorrecto." << std::endl;
    std::cerr << "Uso: ./emst_cliente <fichero_entrada> [-d]" << std::endl;
    usage = true;
  }
  return usage;
}

/**
 * @brief: función main que lee un fichero de puntos y calcula la envolvente convexa
 * @param[in] argc: número de argumentos
 * @param[in] argv: argumentos de la función
 * @return EXIT_FAILURE si ocurre algun inconveniente, EXIT_SUCCESS si todo va bien
 */
int main(int argc, char* argv[]) {
  system("clear");
  if (usage(argc)) return 1;
  std::ofstream dot_file;
  if (argc == 3) {
    std::string option = argv[2];
    if (option == "-d") {
      dot_file.open("hull.dot");
      if (!dot_file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return EXIT_FAILURE;
      }
    }
    else {
      std::cerr << "Error: Opción incorrecta." << std::endl;
      std::cerr << "Uso: ./tree_emst.out <fichero_entrada> [-d]" << std::endl;
      return EXIT_FAILURE;
    }
  }
  std::string filename = argv[1];
  std::ifstream file(filename);
  std::string linea;
  std::getline(file, linea);
  int num_points = std::stoi(linea);
  cya::point_vector points;
  for (int i = 0; i < num_points; i++) {
    cya::point p;
    file >> p.first >> p.second;
    points.push_back(p);
  }
  cya::point_set conjunto_puntos(points);
  conjunto_puntos.quickHullPublic();
  conjunto_puntos.write_hull(std::cout);
  if (argc == 3) {
    conjunto_puntos.write_dot(dot_file);
    std::cout << "Archivo hull.dot generado" << std::endl;
  }
  return EXIT_SUCCESS;
}
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: funciones.cc
// Contiene la implementación de las funciones que usará el programa cliente.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "funciones.h"
#include "alfabeto.h"
#include "cadena.h"
#include "conjunto.h"

/**
 * @brief método que comrpueba si el nº de parametros pasados al main son correctos
 * @param argc nº de parametros pasados al main.
 * @return usage devuelve true o false dependiendo del número.
 */
bool usage(const int& argc) {
  bool usage = true;
  if (argc != 2 && argc != 4) {
    usage = false;
  }
  return usage;
}

/**
 * @brief método que comrpueba si se ha pasado como parametro "--help"
 * @param argc nº de parametros pasados al main.
 * @param help string del parametro en posición 1 de argv[]
 * @return param true o false dependiendo de la comparación.
 */
bool help(const int& argc, const std::string& help) {
  bool param = false;
  if (argc == 2 && help == "--help") param = true;
  return param;
}

/**
 * @brief método que comrpueba si el archivo de entrada está abierto
 * @param file input file stream archvo de entrada.
 * @return open variable booleana true o false dependiendo de si esta abierto o no
 */
bool managefile(const std::ifstream& file) {
  bool open = true;
  if (!file.is_open()) open = false;
  return open;
}

/**
 * @brief esta parte se encarga de ejecutar el programa como tal, haciendo uso de las clases y sus parámetros.
 * @param File fichero de entrada.
 * @param OutFile fichero de salida
 * @param linea linea del fichero de entrada. Es pasada como string.
 * @param opcode string del opcode que se pasa al programa
 */
void programa(std::ifstream& File, std::ofstream& OutFile, std::string& linea, const std::string& opcode) {
  while (std::getline(File, linea)) {
      std::istringstream iss(linea);
      std::string cadena;
      iss >> cadena;
      std::string alfabeto;
      iss >> alfabeto;
      if (opcode == "Alfabeto") {
        Alfabeto Alfabeto{alfabeto};
        OutFile << Alfabeto;
      }
      else if (opcode == "Longitud") {
        Cadena Cadena{cadena};
        Cadena.ImprimeLongitud(OutFile);
      }
      else if (opcode == "Inversa") {
        Cadena Chain{cadena};
        Cadena invertida = Chain.Inversa();
        OutFile << invertida << std::endl;
      }
      else if (opcode == "Prefijos") {
        Cadena Cadena{cadena};
        Conjunto prefijos;
        prefijos.ConjuntoPrefijos(Cadena);
        OutFile << prefijos;
      }
      else if (opcode == "Sufijos") {
        Cadena Cadena{cadena};
        Conjunto sufijos;
        sufijos.ConjuntoSufijos(Cadena);
        OutFile << sufijos << std::endl;
      }
      else if (opcode == "6") {
        Cadena Cadena{cadena};
        Cadena.IgualInversa(OutFile);
      }
      else {
        std::cout << "Opcode Incorrecto" << std::endl;
        std::cout << "Este programa solo acepta los siguientes códigos de operación:" << std::endl;
        std::cout << "Alfabeto" << std::endl;
        std::cout << "Longitud" << std::endl;
        std::cout << "Inversa" << std::endl;
        std::cout << "Prefijos" << std::endl;
        std::cout << "Sufijos" << std::endl;
        std::cout << "6" << std::endl;
        break;
      }
    }
}
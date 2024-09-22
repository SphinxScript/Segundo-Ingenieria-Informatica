// Universidad de La Laguna
// Escuela Superior de Ingenier´ıa y Tecnolog´ıa
// Grado en Ingenier´ıa Inform´atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la funci´on main del proyecto que usa las clases X e Y
// para ... (indicar brevemente el objetivo)
// Referencias:
// Enlaces de inter´es

// Historial de revisiones
// 17/09/2024 - Creaci´on (primera versi´on) del c´odigo


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "funciones.h"
#include "alfabeto.h"
#include "cadena.h"
#include "conjunto.h"

bool usage(const int& argc) {
  bool usage = true;
  if (argc != 2 && argc != 4) {
    usage = false;
  }
  return usage;
}

bool help(const std::string& help) {
  bool param = false;
  if (help == "--help") param = true;
  return param;
}

bool managefile(const std::ifstream& file) {
  bool open = true;
  if (!file.is_open()) open = false;
  return open;
}

void programa(std::ifstream& File, std::ofstream& result, std::string& linea, const std::string& opcode) {
  while (std::getline(File, linea)) {
      std::istringstream iss(linea);
      std::string cadena;
      iss >> cadena;
      std::string alfabeto;
      iss >> alfabeto;
      if (opcode == "Alfabeto") {
        Alfabeto prueba{alfabeto};
        result << prueba;
      }
      else if (opcode == "Longitud") {
        Cadena prueba{cadena};
        prueba.Longitud(result);
      }
      else if (opcode == "Inversa") {
        Cadena prueba{cadena};
        std::string inversa{prueba.Inversa()};
        result << inversa << std::endl;
      }
      else if (opcode == "Prefijos") {
        Cadena prueba{cadena};
        Conjunto prefijos;
        prefijos.ConjuntoPrefijos(prueba);
        result << prefijos;
      }
      else if (opcode == "Sufijos") {
        Cadena prueba{cadena};
        Conjunto sufijos;
        sufijos.ConjuntoSufijos(prueba);
        result << sufijos << std::endl;
      }
      else {
        std::cout << "Opcode Incorrecto" << std::endl;
        break;
      }
    }
}
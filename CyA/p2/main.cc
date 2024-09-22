#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#include "lenguaje.h"


bool usage(const int argc) {
  bool usage = false;
  if (argc != 2 && argc != 4) {
    usage = true;
  }
  return usage;
}

int main(int argc, char* argv[]) {
  if (usage(argc)) {
    std::cout << "Modo de empleo: ./p02_strings filein.txt fileout.txt opcode. Pruebe ./p02_strings --help para más información." << std::endl;
    return 1;
  }
  std::string parametro{argv[1]};
  if (parametro == "--help") {
    std::cout << "imprimir ayuda" << std::endl;
  }
  std::string inputFile{argv[1]};
  std::ifstream File{inputFile};
  if (!File.is_open()) {
    std::cerr << "ERROR. No se puede abrir el archivo de entrada" << std::endl;
    return 1;
  }
  std::string outputFile{argv[2]};        // guarddamos en outputFile el nombre del archivo de salida
  std::string opcode{argv[3]};            // guardamos en opcode el opcode
  std::ofstream result{outputFile};
  std::string linea;
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
      std::cout << prefijos;
    }
    else if (opcode == "Sufijos") {
      Cadena prueba{cadena};
      Conjunto sufijos;
      sufijos.ConjuntoSufijos(prueba);
      std::cout << sufijos << std::endl;
    }
    else {
      std::cout << "Opcode Incorrecto" << std::endl;
      break;
    }
  }
  std::cout << "Éxito" << std::endl;
  return 0;
}
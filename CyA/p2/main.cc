// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: main.cc: programa cliente
// Contiene el programa cliente (main) de la práctica.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "alfabeto.h"
#include "cadena.h"
#include "conjunto.h"
#include "funciones.h"



int main(int argc, char* argv[]){
  if (!usage(argc)) {
    std::cout << "Modo de empleo: ./p02_strings filein.txt fileout.txt opcode. Pruebe ./p02_strings --help para más información." << std::endl;
    return 1;
  }
  std::string parametro{argv[1]};
  if (help(argc, parametro) && argc == 2) {
    std::cout << "imprimir ayuda" << std::endl;
    return 1;
  }
  else {
    std::cout << "parametro incorrecto." << std::endl;
    return 1;
  }
  std::string inputFile{argv[1]};
  std::ifstream File{inputFile};
  if (!managefile(File)) {
    std::cerr << "ERROR. No se puede abrir el archivo de entrada" << std::endl;
    return 1;
  }
  std::string outputFile{argv[2]};        // guarddamos en outputFile el nombre del archivo de salida
  std::string opcode{argv[3]};            // guardamos en opcode el opcode
  std::ofstream OutFile{outputFile};       // OutFile sera el nombre del archivo de salida
  std::string linea;                      // string para almacenar las lineas del archivo de entrada
  programa(File, OutFile, linea, opcode);  // llamamos a la funcion void programa, que se encarga de procesar el opcode y emplear las distintas clases
  return 0;
}
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
  if (help(parametro)) {
    std::cout << "imprimir ayuda" << std::endl;
  }
  std::string inputFile{argv[1]};
  std::ifstream File{inputFile};
  if (!managefile(File)) {
    std::cerr << "ERROR. No se puede abrir el archivo de entrada" << std::endl;
    return 1;
  }
  std::string outputFile{argv[2]};        // guarddamos en outputFile el nombre del archivo de salida
  std::string opcode{argv[3]};            // guardamos en opcode el opcode
  std::ofstream result{outputFile};       // result sera el nombre del archivo de salida
  std::string linea;                      // string para almacenar las lineas del archivo de entrada
  programa(File, result, linea, opcode);  // llamamos a la funcion void programa, que se encarga de procesar el opcode y emplear las distintas clases
  return 0;
}
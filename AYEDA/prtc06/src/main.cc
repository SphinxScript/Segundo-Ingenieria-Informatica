#include <iostream>
#include "arbol.h"
#include "nodo.h"
#include "arbol_b.h"
#include "arbol_e.h"
#include "nif.h"
#include "funciones.h"

#include <random>
#include <fstream>

int main(int argc, char* argv[]) {
  system("clear");
  ArgsConfig configuracion;
  int cod_args = ManageArgs(argc, argv, configuracion);
  if (cod_args != 0) {
    std::cerr << "Error: argumentos no válidos. Use -h o -help para ver la ayuda.\n";
    return cod_args;
  }
  AB<Nif>* arbol = nullptr;
  if (configuracion.tipo_arbol == "abe") {
    arbol = new ABE<Nif>();
  }
  else if (configuracion.tipo_arbol == "abb") {
    arbol = new ABB<Nif>();
  }
  else {
    std::cerr << "Error: tipo de árbol no especificado o no válido.\n";
    return 1;
  }
  switch (configuracion.init) {
    case 'm': {
      std::cout << "Generando secuencia manualmente...\n";
      std::cout << "Introuzca los nif 1 a 1 pulsando enter. Termine introduciendo un caracter no numerico" << std::endl;
      while (true) {
        std::string input;
        std::cin >> input;
        if (!CheckNumber(input)) {
          break;
        }
        Nif nif(std::stol(input));
        arbol->insertar(nif);
      }
      break;
    }
    case 'r': {
      std::cout << "Generando secuencia aleatoria...\n";
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<long> dis(10000000, 99999999);
      for (unsigned i = 0; i < configuracion.elements; ++i) {
        Nif nif(dis(gen));
        arbol->insertar(nif);
      }
      break;
    }
    case 'f': {
      std::cout << "Generando secuencia de fichero...\n";
      std::string file_name = configuracion.filename;
      unsigned size = configuracion.elements;

      std::ifstream input_file(file_name);
      if (!input_file.is_open()) {
        std::cerr << "Error: no se pudo abrir el fichero '" << file_name << "'.\n";
        std::exit(EXIT_FAILURE);
      }
      long nif_value;
      unsigned index = 0;
      while (input_file >> nif_value && index < size) {
        arbol->insertar(Nif(nif_value));
        ++index;
      }

      if (index < size) {
        std::cerr << "Error: el fichero contiene menos NIFs que el tamaño indicado.\n";
        std::exit(EXIT_FAILURE);
      }

      if (input_file >> nif_value) {
        std::cerr << "Aviso: el fichero contiene más NIFs que el tamaño indicado. "
                    "Se ignorarán los restantes.\n";
      }
      break;
    }
    default:
      std::cerr << "Metodo de inicializacion no valido";
      return 1;
  }
  Menu(*arbol);
  delete arbol;
  return 0;
}
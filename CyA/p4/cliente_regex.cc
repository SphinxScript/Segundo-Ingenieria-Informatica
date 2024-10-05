#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "variables.h"
#include "bucles.h"
#include "main.h"

bool usage(const int& argc) {
  bool usage = true;
  if (argc != 3 && argc != 2) {
    usage = false;
  }
  return usage;
}
// void () {

// }

int main(int argc, char* argv[]) {
  system("clear");
  if (!usage(argc)) {
    std::cout << "Modo de empleo: ./regex.oug filein.txt fileout.txt ... Pruebe ./p02_strings --help para más información." << std::endl;
    return 1;
  }
  std::ifstream input_file{argv[1]};
  std::ofstream output_file{argv[2]};
  std::string linea;
  Variables variables;
  Bucles bucles;
  Main main;
  int numero_linea{1};
  if (input_file.is_open()) {
    while (std::getline(input_file, linea)) {
      variables.ProcesarLinea(linea, numero_linea);
      bucles.ProcesarLinea(linea, numero_linea);
      main.ProcesarLinea(linea);
      ++numero_linea;
    }
  }
  output_file << variables;
  output_file << std::endl;
  output_file << bucles;
  output_file << std::endl;
  output_file << main;
  input_file.close();
  return 0;
}
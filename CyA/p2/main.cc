#include <string>
#include <fstream>
#include <vector>
#include <iostream>

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
  std::string outputFile{argv[2]};
  std::ofstream result{outputFile};
  std::string linea;
  while (std::getline(File, linea)) {
    result << linea << std::endl;
  }
  std::cout << "Exito" << std::endl;
  return 0;
}
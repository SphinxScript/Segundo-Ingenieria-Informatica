#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool Usage(int argc) {
  return (argc != 3 && argc != 2) ? false : true;
}

bool CompruebaHelp(const std::string& str) {
  bool help{false};
  if (str == "--help") help = true;
  return help;
}


bool CompruebaGramatica(std::ifstream& input_file) {
  bool valida = true;
  std::string linea;
  std::getline(input_file, linea);
  int terminales{std::stoi(linea)};
  for (int i{0}; i < terminales && std::getline(input_file, linea); ++i) {}
  std::getline(input_file, linea);
  int no_terminales{std::stoi(linea)};
  for (int i{0}; i <= no_terminales && std::getline(input_file, linea); ++i) {}
  while (std::getline(input_file, linea)) {
    char no_terminal;
    std::string produccion;
    std::istringstream iss(linea);
    iss >> no_terminal >> produccion;
    if (produccion.size() == 1) {
      if (isupper(produccion[0])) {
        valida = false;
      }
    }
  }
  return valida;
}

int main(int argc, char* argv[]) {
  system("clear");
  if (!Usage(argc)) {
    std::cerr << "Error en la llamada al programa." << std::endl;
    std::cerr << "Uso: ./grammar2CNF_cliente <fichero_entrada> <fichero_salida>" << std::endl;
    std::cout << "Para más información, ./grammar2CNF_cliente --help" << std::endl;
    return 1;
  }
  if (CompruebaHelp(argv[1])) {
    std::cout << "Este programa convierte una gramática independiente de contexto en una gramática en forma normal de Chomsky." << std::endl;
    std::cout << "Uso: ./grammar2CNF_cliente <fichero_entrada> <fichero_salida>" << std::endl;
    std::cout << "El fichero de entrada debe contener la gramática a convertir, sin producciones inútiles, unitarias ni vacías" << std::endl;
    return 0;
  }
  std::ifstream input_file(argv[1]);
  if (!CompruebaGramatica(input_file)) {
    std::cerr << "Error en la gramática." << std::endl;
  }
  else {
    std::cout << "aquí" << std::endl;
  }
  return 0;
}
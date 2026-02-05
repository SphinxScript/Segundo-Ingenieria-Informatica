#include "funciones.h"
#include <string>



void PrintUsage() {
  std::cout << "Usage: ./langton.out <fichero_entrada> [OPTIONS]\n"
            << "Options:\n"
            << "  --h, --help          Muestra este mensaje y termina\n"
            << "  --g, --guardar       Guarda la salida del programa en el fichero especificado a continuación: \n"
            << "                      -g, --guardar <nombre_fichero>\n";
}

// comprueba si se ha pasado el argumento de ayuda y devuelve true si es así, false en caso contrario
bool ManageHelp(int argc, char* const argv[]) {
  bool help = false;
  for (int i{1}; i < argc; ++i) {
    if (std::string(argv[i]) == "--h" || std::string(argv[i]) == "--help") {
      help = true;
      break;
    }
  }
  return help;
}

void ManageSave(int argc, char* const argv[], bool& guardar_fichero) {
  for (int i{1}; i < argc; ++i) {
    if (std::string(argv[i]) == "--g" || std::string(argv[i]) == "--guardar") {
      guardar_fichero = true;
      break;
    }
  }
}

bool ManageOutFile(int argc, char* const argv[], std::string& nombre_fichero) {
  bool nombre_fichero_ok = false;
  for (int i{1}; i < argc; ++i) {
    if (std::string(argv[i]) == "--g" || std::string(argv[i]) == "--guardar") {
      if (i + 1 < argc) {
        nombre_fichero = argv[i + 1];
        nombre_fichero_ok = true;
      }
      break;
    }
  }
  return nombre_fichero_ok;
}
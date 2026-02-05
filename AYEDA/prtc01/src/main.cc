#include <iostream>

#include "ant.h"
#include "funciones.h"

int main(int argc, char* argv[]) {
  system("clear");
  if (argc < 2) {
    std::cerr << "Error en la invocación del programa.\n";
    PrintUsage();
    return 0;
  }
  if (ManageHelp(argc, argv)) {
    PrintUsage();
    return 0;
  }
  bool guardar_fichero = false;
  std::string nombre_fichero;
  ManageSave(argc, argv, guardar_fichero);
  if (guardar_fichero) {
    if (!ManageOutFile(argc, argv, nombre_fichero)) {
      std::cerr << "Error: No se ha especificado un nombre de fichero válido para guardar la salida.\n";
      return 0;
    }
  }
  std::cout << "debug: nombre_fichero  = " << nombre_fichero << "\n";
  return 0;
}
#include <iostream>

#include "ant.h"
#include "funciones.h"
#include "tape.h"
#include "simulator.h"

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
  std::string fichero_entrada{argv[1]};
  std::cout << "debug: nombre_entrada = " << fichero_entrada << "\n";
  std::cout << "debug: nombre_salida  = " << nombre_fichero << "\n";
  Ant hormiga{};
  Tape rejilla{};
  bool check_build;
  Simulator simulador(fichero_entrada, hormiga, rejilla, check_build);

  if (!check_build) {
    std::cerr << "Error al crear los objetos. finalizando" << std::endl;
    return 1;
  }

  return 0;
}
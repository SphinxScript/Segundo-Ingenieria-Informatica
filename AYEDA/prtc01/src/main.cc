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

  std::string fichero_entrada{argv[1]};
  // std::cout << "debug: nombre_entrada = " << fichero_entrada << "\n";
  // std::cout << "debug: nombre_salida  = " << nombre_fichero << "\n";
  bool check_build;
  Simulator simulador(fichero_entrada, check_build);

  if (!check_build) {
    std::cerr << "Error al crear los objetos. finalizando" << std::endl;
    return 1;
  }
  std::cout << simulador.GetTape() << std::endl;
  simulador.Simulate();
  std::cout << "Desea guardar el resultado en un fichero? (s/n): ";
  char respuesta;
  std::cin >> respuesta;
  std::string fichero_salida;
  if (respuesta == 's' || respuesta == 'S') {
    std::cout << "Introduzca nombre de fichero: ";
    std::cin >> fichero_salida;
    HandleSave(fichero_salida, simulador);
  }
  return 0;
}
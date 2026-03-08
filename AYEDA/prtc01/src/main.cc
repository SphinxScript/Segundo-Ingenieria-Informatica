#include <iostream>

#include "ant/ant.h"
#include "funciones.h"
#include "tape/tape.h"
#include "simulator.h"
#include "ant/ant_reglas.h"

/**
 * @brief Función principal del programa. Se encarga de gestionar la entrada de datos, crear los objetos necesarios y ejecutar la simulación.
 * @param argc Número de argumentos de la línea de comandos.
 * @param argv Vector de argumentos de la línea de comandos.
 * @return Código de salida del programa.
 */
int main(int argc, char* argv[]) {
  system("clear");
  if (argc < 3) {
    std::cerr << "Error en la invocación del programa.\n";
    PrintUsage();
    return 0;
  }
  if (ManageHelp(argc, argv)) {
    PrintUsage();
    return 0;
  }

  std::string fichero_entrada{argv[1]};
  int tipo_cinta = std::stoi(argv[2]);
  if (tipo_cinta < 1 || tipo_cinta > 3) {
    std::cerr << "Error: tipo de cinta desconocido (" << tipo_cinta << ").\n";
    PrintUsage();
    return 0;
  }
  // std::cout << "debug: nombre_entrada = " << fichero_entrada << "\n";
  // std::cout << "debug: nombre_salida  = " << nombre_fichero << "\n";
  bool check_build;
  //std::cout << "debug: creando objetos...\n";
  Simulator simulador(fichero_entrada, check_build, tipo_cinta);

  if (!check_build) {
    std::cerr << "Error al crear los objetos. finalizando" << std::endl;
    return 1;
  }
  std::cout << "Introduzca 1 si quiere simular paso a paso. No introduzca nada si quiere simular automáticamente: ";
  std::string opcion;
  getline(std::cin, opcion);
  if (opcion == "1") {
    std::cout << "Simulación paso a paso seleccionada.\n";
  }
  else {
    std::cout << "Simulación automática seleccionada.\n";
  }
  std::cout << "Rejilla inicial: \n" << simulador << std::endl;
  simulador.Simulate(opcion == "1" ? 1 : 0);

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
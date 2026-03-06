#include "funciones.h"
#include <string>
#include "ant/ant_reglas.h"


/**
 * @brief Imprime el mensaje de uso del programa.
 */
void PrintUsage() {
  std::cout << "Usage: ./langton.out <fichero_entrada> [OPTIONS]\n"
            << "Options:\n"
            << "  --h, --help          Muestra este mensaje y termina\n";
}

/**
 * @brief Comprueba si se ha pasado el argumento de ayuda en la línea de comandos.
 * @param argc Número de argumentos de la línea de comandos.
 * @param argv Vector de argumentos de la línea de comandos.
 * @return true si se ha pasado el argumento de ayuda, false en caso contrario.
 */
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

/**
 * @brief Guarda el estado final de la simulación en un fichero de salida.
 * @param fichero_salida Nombre del fichero donde se guardará el resultado.
 * @param simulador Objeto Simulator que contiene el estado final de la simulación.
 */
void HandleSave(const std::string& fichero_salida, const Simulator& simulador) {
  std::ofstream flujo_salida{fichero_salida};
  flujo_salida << simulador.GetTape().GetSize().first << " " << simulador.GetTape().GetSize().second << " " << simulador.GetTape().GetNumColores() << std::endl;
  // bucle para guardar el estado de cada hormig
  for (int i{0}; i < static_cast<int>(simulador.GetAnts().size()); ++i) {
    if (i == static_cast<int>(simulador.GetAnts().size()) - 1) {
      flujo_salida << simulador.GetAnts()[i]->GetReglas() << " " << simulador.GetAnts()[i]->GetPosition().first
                   << " " << simulador.GetAnts()[i]->GetPosition().second << " " << static_cast<int>(simulador.GetAnts()[i]->GetOrientacion());
    }
    else {
      flujo_salida << simulador.GetAnts()[i]->GetReglas() << " " << simulador.GetAnts()[i]->GetPosition().first
                   << " " << simulador.GetAnts()[i]->GetPosition().second << " " << static_cast<int>(simulador.GetAnts()[i]->GetOrientacion()) << " ; ";
    }
  }
  flujo_salida << std::endl;
  // bucle para guardar el estado de cada celda de la rejilla
  auto [filas, columnas] = simulador.GetTape().GetSize();
  for (int i{0}; i < filas; ++i) {
    for (int j{0}; j < columnas; ++j) {
      if (static_cast<int>(simulador.GetTape().GetColor(i, j)) != 0) {
        flujo_salida << i << " " << j << " " << static_cast<int>(simulador.GetTape().GetColor(i, j)) << std::endl;
      }
    }
  }
}
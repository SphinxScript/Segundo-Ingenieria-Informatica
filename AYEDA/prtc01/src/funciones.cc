#include "funciones.h"
#include <string>


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
  flujo_salida << simulador.GetTape().GetSize().first << " " << simulador.GetTape().GetSize().second << std::endl;
  flujo_salida << simulador.GetAnt().GetPosition().first << " " << simulador.GetAnt().GetPosition().second << " " << static_cast<int>(simulador.GetAnt().GetOrientacion()) << std::endl;
  for (int i{0}; i < simulador.GetTape().GetMalla().size(); ++i) {
    for (int j{0}; j < simulador.GetTape().GetMalla()[i].size(); ++j) {
      if (simulador.GetTape().GetMalla()[i][j]) {
        flujo_salida << i << " " << j;
        flujo_salida << std::endl;
      }
    }
  }
}
#include "funciones.h"
#include <string>
#include "ant/ant_reglas.h"


/**
 * @brief Imprime el mensaje de uso del programa.
 */
void PrintUsage() {
  std::cout << "Usage: ./langton.out <fichero_entrada> <tipo_cinta> [OPTIONS]\n"
            << "Options:\n"
            << "  --h, --help          Muestra este mensaje y termina\n"
            << "Tipo de cinta:\n"
            << "  1: cinta periódica\n"
            << "  2: cinta reflectante\n"
            << "  3: cinta deslizante\n"
            << "Ejemplo de invocación: ./langton.out input.txt 1\n";
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
                   << " " << simulador.GetAnts()[i]->GetPosition().second << " " << static_cast<int>(simulador.GetAnts()[i]->GetOrientacion())
                   << " " << simulador.GetAnts()[i]->GetLifeTime();
    }
    else {
      flujo_salida << simulador.GetAnts()[i]->GetReglas() << " " << simulador.GetAnts()[i]->GetPosition().first
                   << " " << simulador.GetAnts()[i]->GetPosition().second << " " << static_cast<int>(simulador.GetAnts()[i]->GetOrientacion())
                   << " " << simulador.GetAnts()[i]->GetLifeTime() << " ; " ;
    }
  }
  int min_x = simulador.GetTape().Minx();
  int max_x = simulador.GetTape().Maxx();
  int min_y = simulador.GetTape().Miny();
  int max_y = simulador.GetTape().Maxy();
  flujo_salida << std::endl;
  for (int i{min_x}; i <= max_x; ++i) {
    for (int j{min_y}; j <= max_y; ++j) {
      if (static_cast<int>(simulador.GetTape().GetColor(i, j)) != 0) {
        flujo_salida << i << " " << j << " " << static_cast<int>(simulador.GetTape().GetColor(i, j)) << std::endl;
      }
    }
  }
}
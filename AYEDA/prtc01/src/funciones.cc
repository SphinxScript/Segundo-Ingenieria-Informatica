#include "funciones.h"
#include <string>



void PrintUsage() {
  std::cout << "Usage: ./langton.out <fichero_entrada> [OPTIONS]\n"
            << "Options:\n"
            << "  --h, --help          Muestra este mensaje y termina\n";
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
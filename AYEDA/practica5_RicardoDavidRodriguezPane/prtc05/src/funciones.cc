#include <iostream>
#include <string>

#include "funciones.h"

/**
 * @brief PrintHelp muestra la ayuda de uso del programa.
 */
void PrintHelp() {
  std::cout
      << "Uso:\n"
      << "  ./programa -size <s> -ord <m> -init <manual|random|file> [fichero] "
         "-trace <y|n>\n"
      << "  ./programa -h\n"
      << "  ./programa --help\n\n"
      << "Opciones:\n"
      << "  -size <s>              Tamano de la secuencia.\n"
      << "  -ord <m>               Metodo de ordenacion:\n"
      << "                            s  Seleccion\n"
      << "                            b  Burbuja\n"
      << "                            m  MergeSort\n"
      << "                            h  HeapSort\n"
      << "                            i  Incrementos decrecientes\n"
      << "  -init <i> [f]          Inicializacion de la secuencia:\n"
      << "                            manual\n"
      << "                            random\n"
      << "                            file <fichero>\n"
      << "  -trace <y|n>           Muestra o no la traza.\n";
}

/**
 * @brief CheckArg verifica si el argumento es una opción válida.
 * @param arg El argumento a verificar.
 * @return true si el argumento es válido, false en caso contrario.
 */
bool CheckArg(const std::string& arg) {
  return arg == "-size" || arg == "-ord" || arg == "-init" || arg == "-trace" || arg == "-h" || arg == "--help";
}

/**
 * @brief CheckNumber verifica si una cadena representa un número válido.
 * @param cadena La cadena a verificar.
 * @return true si la cadena representa un número válido, false en caso contrario.
 */
bool CheckNumber(const std::string& cadena) {
  try {
    size_t pos = 0;
    std::stoi(cadena, &pos);
    return pos == cadena.size();
  } catch (const std::invalid_argument&) {
    return false;
  } catch (const std::out_of_range&) {
    return false;
  }
}

/**
 * @brief ManageArgs procesa los argumentos de la línea de comandos y llena la estructura ArgsConfig.
 * @param argc Número de argumentos.
 * @param argv Arreglo de argumentos.
 * @param argumentos Estructura donde se almacenarán los argumentos procesados.
 * @return 0 si los argumentos son válidos, un código de error en caso contrario.
 */
int ManageArgs(int argc, char* argv[], ArgsConfig& argumentos) {
  if (argc == 2) {
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
      PrintHelp();
      return 1;
    }
  }

  bool has_size = false;
  bool has_ord = false;
  bool has_init = false;
  bool has_trace = false;

  for (int i = 1; i < argc; ++i) {
    std::string option = argv[i];

    if (!CheckArg(option)) {
      return 1;
    }

    if (option == "-h" || option == "--help") {
      PrintHelp();
      return 1;
    }

    if (option == "-size") {
      if (has_size) {
        return 1;
      }
      ++i;
      if (i >= argc || !CheckNumber(argv[i])) {
        return 1;
      }

      int value = std::stoi(argv[i]);
      if (value <= 0) {
        return 1;
      }

      argumentos.tablesize = static_cast<unsigned>(value);
      has_size = true;
    }
    else if (option == "-ord") {
      if (has_ord) {
        return 1;
      }
      ++i;
      if (i >= argc) {
        return 1;
      }

      std::string method = argv[i];
      if (method.size() != 1) {
        return 1;
      }

      char code = method[0];
      if (code != 's' && code != 'b' && code != 'm' && code != 'h' && code != 'i') {
        return 1;
      }

      argumentos.method = code;
      has_ord = true;
    }
    else if (option == "-init") {
      if (has_init) {
        return 1;
      }
      ++i;
      if (i >= argc) {
        return 1;
      }

      std::string init_mode = argv[i];

      if (init_mode == "manual") {
        argumentos.init = 'm';
      }
      else if (init_mode == "random") {
        argumentos.init = 'r';
      }
      else if (init_mode == "file") {
        argumentos.init = 'f';
        ++i;
        if (i >= argc) {
          return 1;
        }
        argumentos.fichero = argv[i];
        if (argumentos.fichero.empty()) {
          return 1;
        }
      }
      else {
        return 1;
      }

      has_init = true;
    }
    else if (option == "-trace") {
      if (has_trace) {
        return 1;
      }
      ++i;
      if (i >= argc) {
        return 1;
      }
      std::string trace_value = argv[i];
      if (trace_value == "y") {
        argumentos.trace = true;
      }
      else if (trace_value == "n") {
        argumentos.trace = false;
      }
      else {
        return 1;
      }

      has_trace = true;
    }
  }

  if (!has_size || !has_ord || !has_init || !has_trace) {
    return 1;
  }

  return 0;
}
#include <iostream>
#include <string>

#include "funciones.h"

/**
 * @brief PrintHelp muestra la ayuda de uso del programa.
 */
void PrintHelp() {
  std::cout
      << "Uso:\n"
      << "  ./programa -ab <abe|abb> -init <manual|random|file> [s] [f]\n"
      << "  ./programa -h\n"
      << "  ./programa --help\n\n"
      << "Opciones:\n"
      << "  -ab <abe|abb>          Tipo de arbol.\n"
      << "  -init manual           Arbol vacio.\n"
      << "  -init random <s>       Genera s elementos aleatorios.\n"
      << "  -init file <s> <f>     Lee s elementos desde fichero.\n";
}

/**
 * @brief CheckArg verifica si el argumento es una opción válida.
 * @param arg El argumento a verificar.
 * @return true si el argumento es válido, false en caso contrario.
 */
bool CheckArg(const std::string& arg) {
  return arg == "-ab" || arg == "-init" || arg == "-help" || arg == "-h";
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
    if (arg == "-h" || arg == "-help") {
      PrintHelp();
      return 1;
    }
  }

  bool has_tree_type = false;
  bool has_init = false;

  for (int i = 1; i < argc; ++i) {
    std::string option = argv[i];

    if (!CheckArg(option)) {
      std::cerr << "Error: argumento no reconocido '" << option << "'.\n";
      return 1;
    }

    if (option == "-h" || option == "-help") {
      PrintHelp();
      return 1;
    }

    if (option == "-ab") {
      if (has_tree_type) {
        return 1;
      }
      ++i;
      if (i >= argc) {
        return 1;
      }
      std::string tipo = argv[i];
      if (tipo != "abe" && tipo != "abb") {
        return 1;
      }
      argumentos.tipo_arbol = tipo;
      has_tree_type = true;
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
        ++i;
        if (i >= argc || !CheckNumber(argv[i])) {
          return 1;
        }
        unsigned elements = std::stoul(argv[i]);
        argumentos.elements = elements;
      }
      else if (init_mode == "file") {
        argumentos.init = 'f';
        ++i;
        if (i >= argc || !CheckNumber(argv[i])) {
          return 1;
        }
        unsigned elements = std::stoul(argv[i]);
        ++i;
        if (i >= argc) {
          return 1;
        }
        argumentos.filename = argv[i];
        argumentos.elements = elements;
      }
      else {
        return 1;
      }
      has_init = true;
    }
  }

  if (!has_tree_type || !has_init) {
    return 1;
  }

  return 0;
}


void ShowMenu() {
  std::cout << "Seleccione una opción:\n";
  std::cout << "1. Insertar un NIF\n";
  std::cout << "2. Buscar un NIF\n";
  std::cout << "3. Mostrar el árbol inorden\n";
  std::cout << "4. Mostrar el árbol por niveles\n";
  std::cout << "0. Salir\n";
  std::cout << "Opción: ";
}
#include <iostream>

#include "funciones.h"

void PrintHelp() {
  std::cout
            << "Uso:\n"
            << "  ./programa -ts <table_size> -fd <fd_code> -hash <open|close> "
              "[-bs <block_size> -fe <fe_code>]\n"
            << "  ./programa -h\n"
            << "  ./programa --help\n\n"
            << "Opciones:\n"
            << "  -h, --help          Muestra esta ayuda y termina.\n"
            << "  -ts <table_size>    Tamaño de la tabla hash.\n"
            << "  -fd <fd_code>       Función de dispersión:\n"
            << "                         0  Módulo\n"
            << "                         1  Suma\n"
            << "                         2  Pseudoaleatoria\n"
            << "  -hash <type>        Tipo de tabla hash:\n"
            << "                         open   Dispersión abierta\n"
            << "                         close  Dispersión cerrada\n"
            << "  -bs <block_size>    Tamaño del bloque (solo con -hash close).\n"
            << "  -fe <fe_code>       Función de exploración (solo con -hash close):\n"
            << "                         0  Lineal\n"
            << "                         1  Cuadrática\n"
            << "                         2  Doble dispersión\n"
            << "                         3  Redispersión\n";
}

bool CheckArg(const std::string& arg) {
  if (arg == "-ts" || arg == "-fd" || arg == "-hash" || arg == "-bs" || arg == "-fe") {
    return true;
  }
  return false;
}

bool CheckNumber(const std::string& cadena) {
  try {
    std::stoi(cadena);
  }
  catch (const std::invalid_argument&) {
    return false;
  }
  catch (const std::out_of_range&) {
    return false;
  }
  return true;
}

int ManageArgs(int argc, char* argv[], ArgsConfig& argumentos) {
  bool close = false;
  bool bool_block = false;
  bool bool_fe = false;
  bool bool_ts = false;
  bool bool_fd = false;
  bool bool_hash = false;
  for (int i{1}; i < argc; ++i) {
    std::string opcion = argv[i];
    if (!CheckArg(opcion)) {
      return 1;
    }
    if (opcion == "-ts") {
      if (bool_ts) return 1;
      ++i;
      if (i >= argc) return 1;
      if (!CheckNumber(argv[i])) return 1;
      int tablesize = std::stoi(argv[i]);
      if (tablesize <= 0) return 1;
      argumentos.tablesize = tablesize;
      bool_ts = true;
    }
    else if (opcion == "-fd") {
      if (bool_fd) return 1;
      ++i;
      if (i >= argc) return 1;
      if (!CheckNumber(argv[i])) return 1;
      int fd = std::stoi(argv[i]);
      if (fd < 0 || fd > 2) return 1;
      argumentos.fd = fd;
      bool_fd = true;
    }
    else if (opcion == "-hash") {
      if (bool_hash) return 1;
      ++i;
      if (i >= argc) return 1;
      std::string abierto_cerrado = argv[i];
      if (abierto_cerrado != "open" && abierto_cerrado != "close") return 1;
      if (abierto_cerrado[0] == 'c') close = true;
      argumentos.dispersion = abierto_cerrado[0];
      bool_hash = true;
    }
    else if (opcion == "-bs") {
      if (bool_block) return 1;
      ++i;
      if (i >= argc) return 1;
      if (!CheckNumber(argv[i])) return 1;
      int blocksize = std::stoi(argv[i]);
      if (blocksize <= 0) return 1;
      argumentos.blocksize = blocksize;
      bool_block = true;
    }
    else if (opcion == "-fe") {
      if (bool_fe) return 1;
      ++i;
      if (i >= argc) return 1;
      if (!CheckNumber(argv[i])) return 1;
      int fe = std::stoi(argv[i]);
      if (fe < 0 || fe > 3) return 1;
      argumentos.fe = fe;
      bool_fe = true;
    }
  }
  if (!bool_ts || !bool_fd || !bool_hash) return 1;     // no pasaron alguno de los obligatorios
  if (close || bool_fe || bool_block) {
    if (!close) return 2;
    if (!bool_fe) return 3;
    if (!bool_block) return 4;
  }
  return 0;
}

void ShowMenu() {
  std::cout << "Introduzca 1 Para insertar, 2 para buscar un valor" << std::endl;
  std::cout << "Introduzca 0 para salir" << std::endl;
}
#pragma once

#include <string>
#include <vector>

#include "nif.h"

struct ArgsConfig {
  unsigned tablesize;
  unsigned fd;
  char dispersion;    // o -> open ; c -> close
  unsigned blocksize;
  unsigned fe;
};


void PrintHelp();

bool CheckArg(const std::string& arg);

bool CheckNumber(const std::string& cadena);

int ManageArgs(int argc, char* argv[], ArgsConfig& argumentos);

void ShowMenu();

template <class Table>
void Menu(Table& tabla_hash) {
  while (true) {
    ShowMenu();
    int opcion;
    std::cin >> opcion;
    if (opcion != 1 && opcion != 2 && opcion != 0) {
      std::cout << "opcion no valida; repita\n";
      continue;
    }
    if (opcion == 0) break;
    if (opcion == 1) {
      std::cout << "Introduzca un NIF: ";
      long nif; std::cin >> nif;
      Nif objeto_nif(nif);
      if(tabla_hash.Insert(objeto_nif)) {
        std::cout << std::endl << "Insertado con éxito!" << std::endl;
      }
      else {
        std::cout << "No insertado... :(" << std::endl;
      }
    }
    if (opcion == 2) {
      std::cout << "Introduzca un NIF: ";
      long nif;
      std::cin >> nif;
      Nif objeto_nif(nif);
      if(tabla_hash.Search(objeto_nif)) {
        std::cout << std::endl << "Localizado!" << std::endl;
      }
      else {
        std::cout << "No encontrado... :(" << std::endl;
      }
    }
    std::cout << "\n\n";
  }
}
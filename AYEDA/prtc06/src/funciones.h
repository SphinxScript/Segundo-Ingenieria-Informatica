#pragma once

#include <string>
#include <vector>

#include "nif.h"
#include "arbol.h"

/**
 * @brief ArgsConfig es una estructura que almacena la configuración de los argumentos de la línea de comandos.
 */
struct ArgsConfig {
  std::string tipo_arbol;
  char init;
  unsigned elements;
  std::string filename;
};


/**
 * @brief PrintHelp muestra la ayuda de uso del programa.
 */
void PrintHelp();

/**
 * @brief CheckArg verifica si el argumento es una opción válida.
 * @param arg El argumento a verificar.
 * @return true si el argumento es válido, false en caso contrario.
 */
bool CheckArg(const std::string& arg);

/**
 * @brief CheckNumber verifica si una cadena representa un número válido.
 * @param cadena La cadena a verificar.
 * @return true si la cadena representa un número válido, false en caso contrario.
 */
bool CheckNumber(const std::string& cadena);

/**
 * @brief ManageArgs procesa los argumentos de la línea de comandos y llena la estructura ArgsConfig.
 * @param argc Número de argumentos.
 * @param argv Arreglo de argumentos.
 * @param argumentos Estructura donde se almacenarán los argumentos procesados.
 * @return 0 si los argumentos son válidos, un código de error en caso contrario.
 */
int ManageArgs(int argc, char* argv[], ArgsConfig& argumentos);

void ShowMenu();

/**
 * @brief Menu muestra el menú de opciones para el usuario y maneja las interacciones con la tabla hash.
 * @param arbol La tabla hash con la que se interactuará.
 */
template <class T>
void Menu(AB<T>& arbol) {
  while (true) {
    ShowMenu();
    int opcion;
    std::cin >> opcion;
    if (opcion != 1 && opcion != 2 && opcion != 0 && opcion != 3 && opcion != 4) {
      std::cout << "opcion no valida; repita\n";
      continue;
    }
    if (opcion == 0) break;
    if (opcion == 1) {
      std::cout << "Introduzca un NIF: ";
      long nif; std::cin >> nif;
      Nif objeto_nif(nif);
      if(arbol.insertar(objeto_nif)) {
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
      if(arbol.buscar(objeto_nif)) {
        std::cout << std::endl << "Localizado!" << std::endl;
      }
      else {
        std::cout << "\nNo encontrado... :(" << std::endl;
      }
    }
    if (opcion == 3) {
      std::cout << "\nMostrando el árbol inorden...\n";
      arbol.inorden(std::cout);
    }
    if (opcion == 4) {
      std::cout << "\nMostrando el árbol por niveles...\n";
      arbol.mostrar_por_niveles(std::cout);
    }
    std::cout << "\n\n";
  }
}
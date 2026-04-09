#pragma once

#include <string>
#include <vector>

#include "persona.h"
#include "nif.h"

/**
 * @brief ArgsConfig es una estructura que almacena la configuración de los argumentos de la línea de comandos.
 */
struct ArgsConfig {
  unsigned tablesize;
  unsigned fd;
  char dispersion;    // o -> open ; c -> close
  unsigned blocksize;
  unsigned fe;
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

/**
 * @brief ShowMenu muestra el menú de opciones para el usuario.
 */
void ShowMenu();

/**
 * @brief Menu muestra el menú de opciones para el usuario y maneja las interacciones con la tabla hash.
 * @param tabla_hash La tabla hash con la que se interactuará.
 */
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
      std::cout << "Introduzca un NIF, Nombre y edad: --- <NIF> <nombre> <edad> ";

      long nif;
      std::string nombre;
      unsigned edad;
      std::cin >> nif >> nombre >> edad;
      
      Persona objeto_nif(nif, nombre, edad);
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
      Persona objeto_nif(nif);
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
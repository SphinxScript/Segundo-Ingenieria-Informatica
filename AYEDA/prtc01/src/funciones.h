#pragma once
#include <iostream>
#include <fstream>
#include "ant.h"
#include "tape.h"
#include "simulator.h"

/**
 * @brief Función para imprimir el mensaje de uso del programa.
 */
bool ManageHelp(int, char* const*);

/**
 * @brief Función para guardar el estado final de la simulación en un fichero de salida.
 * @param fichero_salida Nombre del fichero donde se guardará el resultado.
 * @param simulador Objeto Simulator que contiene el estado final de la simulación.
 */
void HandleSave(const std::string&, const Simulator&);

/**
 * @brief Función para imprimir el mensaje de uso del programa.
 */
void PrintUsage();

// Universidad de La Laguna
// Escuela Superior de Ingenier´ıa y Tecnolog´ıa
// Grado en Ingenier´ıa Inform´atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la funci´on main del proyecto que usa las clases X e Y
// para ... (indicar brevemente el objetivo)
// Referencias:
// Enlaces de inter´es

// Historial de revisiones
// 17/09/2024 - Creaci´on (primera versi´on) del c´odigo


#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
#include <iostream>
#include <sstream>

bool usage(const int& argc);
bool help(const std::string& help);
bool managefile(const std::ifstream& file);
void programa(std::ifstream& File, std::ofstream& result, std::string& linea, const std::string& opcode);

#endif
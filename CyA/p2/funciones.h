// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: funciones.h
// Contiene la definición de las funciones que se usarán en el programa cliente.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código


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
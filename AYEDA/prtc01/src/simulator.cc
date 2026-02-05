#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "simulator.h"



Simulator::Simulator(const std::string& fichero_entrada, Ant& hormiga, Tape& rejilla, bool& control) {

  std::ifstream flujo_entrada{fichero_entrada};
  if (!flujo_entrada.is_open()) {
    std::cerr << "No se ha podido abrir el fichero de entrada.\n";
    control = false;
    return;
  }
  // capturamos el tamaño de la rejilla
  int sizeX, sizeY;
  flujo_entrada >> sizeX >> sizeY;
  std::cout << "Debug: nº filas columnas" << sizeX << sizeY <<  std::endl;
  int positionX, positionY, orientacion;
  flujo_entrada >> positionX >> positionY >> orientacion;
  std::cout << "debug: posicion y orientacion: " << positionX << positionY << orientacion << std::endl;

  rejilla.SetSize(sizeX, sizeY);
  hormiga.SetPlace(positionX, positionY, orientacion);
  std::string linea;

  while (std::getline(flujo_entrada, linea)) {
    // cada linea es una posición de la rejilla que pasa de blanco (0) por defecto a negro(1)
    int coordx, coordy;
    std::stringstream flujo_linea{linea};
    flujo_linea >> coordx >> coordy;
    rejilla.FlipColor(coordx, coordy);
  }
  control = true;
}

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "simulator.h"
#include "tape.h"



Simulator::Simulator(const std::string& fichero_entrada, bool& control) {

  std::ifstream flujo_entrada{fichero_entrada};
  if (!flujo_entrada.is_open()) {
    std::cerr << "No se ha podido abrir el fichero de entrada.\n";
    control = false;
    return;
  }
  // capturamos el tamaño de la rejilla
  int sizeX, sizeY;
  flujo_entrada >> sizeX >> sizeY;
  // std::cout << "Debug: nº filas columnas" << sizeX << " " << sizeY <<  std::endl;
  int positionX, positionY, orientacion;
  flujo_entrada >> positionX >> positionY >> orientacion;
  // std::cout << "debug: posicion y orientacion: " << positionX << " " << positionY << " " << orientacion << std::endl;
  if (positionX < 0 || positionX >= sizeX || positionY < 0 || positionY >= sizeY) {
    std::cerr << "Error: La posición inicial de la hormiga no es válida.\n";
    control = false;
    return;
  }
  rejilla_.SetSize(sizeX, sizeY);
  hormiga_.SetPlace(positionX, positionY, orientacion);
  std::string linea;
  std::getline(flujo_entrada, linea);

  while (std::getline(flujo_entrada, linea)) {
    // cada linea es una posición de la rejilla que pasa de blanco (0) por defecto a negro(1)
    if (linea.empty()) continue;
    int x, y;
    std::stringstream flujo_linea{linea};
    flujo_linea >> x >> y;
    
    rejilla_.FlipColor(x, y);
    std::cout << x << " " << y << std::endl;
  }
  // ahora asignamos el puntero de la hormiga al objeto cinta.
  rejilla_.SetAnt(&hormiga_);
  control = true;
}

void Simulator::Simulate() {
  std::cout << "Presione enter para avanzar, cualquier otra tecla + enter para finalizar";  
  std::string input;
  bool paso_valido{true};
  int contador{0};
  while(true && paso_valido) {
    getline(std::cin, input);
    if (!input.empty()) break;
    else {
      paso_valido = Step(contador);
    }
  }
  std::cout << "finalizando simulación..." << std::endl;
}

bool Simulator::Step(int& contador) {
  bool valido = hormiga_.Move(rejilla_.GetMalla()[hormiga_.GetPosition().first][hormiga_.GetPosition().second], rejilla_);
  system("clear");
  std::cout << rejilla_;
  std::cout << std::endl;
  std::cout << "Paso " << contador << std::endl;
  ++contador;
  return valido;
}
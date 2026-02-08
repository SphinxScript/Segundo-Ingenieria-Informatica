#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "simulator.h"
#include "tape.h"


/**
 * @brief Constructor de la clase Simulator. Se encarga de leer el fichero de entrada, inicializar la rejilla y la hormiga, y establecer el estado inicial de la simulación.
 * @param fichero_entrada Nombre del fichero de entrada que contiene la configuración inicial de la simulación.
 * @param control Referencia a un booleano que se establece a true si la inicialización es exitosa, o a false si ocurre algún error durante la lectura del fichero o la configuración
 */
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
    //std::cout << "debug: intercambiando casilla:" << x << " " << y << std::endl;
  }
  // ahora asignamos el puntero de la hormiga al objeto cinta.
  rejilla_.SetAnt(&hormiga_);
  control = true;
}

/**
 * @brief Ejecuta la simulación de Langton según la opción seleccionada.
 * @param opcion Opción de simulación (1 para paso a paso, otro valor para ejecución continua).
 * @return void
 */
void Simulator::Simulate(const int& opcion) {
  std::cout << "Presione enter para avanzar, cualquier otra tecla + enter para finalizar";  
  std::string input;
  bool paso_valido{true};
  int contador{0};
  while(true && paso_valido) {
    if (opcion == 1) {
      getline(std::cin, input);
      if (!input.empty()) break;
      else {
        paso_valido = Step(contador);
      }
    }
    else {
      paso_valido = Step(contador);
    }
  }
  std::cout << "finalizando simulación..." << std::endl;
}

/**
 * @brief Ejecuta un paso de la simulación, moviendo la hormiga y actualizando la rejilla.
 * @param contador Referencia a un contador que se incrementa en cada paso para llevar el seguimiento del número de pasos realizados.
 * @return true si el paso es válido (dentro de los límites de la rejilla), false si la hormiga se sale de la rejilla.
 */
bool Simulator::Step(int& contador) {
  bool valido = hormiga_.Move(rejilla_.GetMalla()[hormiga_.GetPosition().first][hormiga_.GetPosition().second], rejilla_);
  system("clear");
  std::cout << rejilla_;
  std::cout << std::endl;
  std::cout << "Paso " << contador << std::endl;
  ++contador;
  return valido;
}
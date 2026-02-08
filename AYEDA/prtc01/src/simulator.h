#pragma once

#include "ant.h"
#include "tape.h"

/**
 * @brief Clase que representa el simulador del juego de la hormiga de Langton. Contiene los objetos Ant y Tape, y métodos para ejecutar la simulación.
 */
class Simulator  {
 public:
  Simulator(const std::string& fichero_entrada, bool& control);
  
  Ant GetAnt() const { return hormiga_; }
  Tape GetTape() const { return rejilla_; }

  void Simulate(const int& opcion = 0);  // si la opción es 0, se simula automático. Si es 1, se simula paso a paso.

  friend std::ostream& operator<<(std::ostream& os, const Simulator& simulator);

 private:
  // Aquí tenemos como atributos privados los objetos cinta y hormiga.
  // trabajaremos con ellos a través de esta clase simulator.
  Ant hormiga_;
  Tape rejilla_;
  // Esta función se encarga de ejecutar el paso de la hormiga
  // Devuelve true si es el paso correcto (dentro de la rejilla)
  // false en caso contrario
  // Esta función se ejecuta cuando el usuario presiona una tecla
  // y se encarga de mover la hormiga, cambiar el color de la celda y actualizar la rejilla.
  // devuelve el control a Simulate() al terminar, se ejecuta en un bucle
  bool Step(int&);
};
#pragma once

#include "ant.h"
#include "tape.h"

class Simulator  {
 public:
  Simulator(const std::string& fichero_entrada, bool& control);
  
  Ant GetAnt() const { return hormiga_; }
  Tape GetTape() const { return rejilla_; }

  void Simulate();

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
  bool Step();
};
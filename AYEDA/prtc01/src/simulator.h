#pragma once

#include "ant/ant.h"
#include "tape/tape.h"
#include "ant/ant_reglas.h"

/**
 * @brief Clase que representa el simulador del juego de la hormiga de Langton. Contiene los objetos Ant y Tape, y métodos para ejecutar la simulación.
 */
class Simulator  {
 public:
  Simulator(const std::string& fichero_entrada, bool& control);
  ~Simulator();
  
  const std::vector<Ant*>& GetAnts() const { return hormigas_; }
  const Tape& GetTape() const { return rejilla_; }

  void Simulate(const int& opcion = 0);  // si la opción es 0, se simula automático. Si es 1, se simula paso a paso.

  friend std::ostream& operator<<(std::ostream& os, const Simulator& simulator);

 private:
  // Aquí tenemos como atributos privados los objetos cinta y hormiga.
  // trabajaremos con ellos a través de esta clase simulator.
  std::vector<Ant*> hormigas_;
  Tape rejilla_;
  std::string ColorHormiga(const Ant&) const;
  void ClearAnts();
  bool Step(int&);
};
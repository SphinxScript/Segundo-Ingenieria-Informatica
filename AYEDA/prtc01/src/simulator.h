#pragma once

#include "ant.h"
#include "tape.h"

class Simulator  {
 public:
  Simulator(const std::string& fichero_entrada, Ant& hormiga, Tape& rejilla, bool& control);
  friend std::ostream& operator<<(std::ostream& os, const Simulator& simulator);
 private:
  // Aquí tenemos como atributos privados los objetos cinta y hormiga.
  // trabajaremos con ellos a través de esta clase simulator.
  Ant ant_;
  Tape tape_;
};
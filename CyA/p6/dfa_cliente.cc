#include <iostream>
#include <fstream>
#include <sstream>

#include "alfabeto.h"
#include "cadena.h"
#include "dfa.h"


int main(int argc, char* argv[]) {
  std::fstream inputfile{argv[1]};
  std::string linea;
  std::vector<Alfabeto> alfabetos;
  while (std::getline(inputfile, linea)) {
    Alfabeto alfabeto{linea};
    alfabetos.push_back(alfabeto);
  }
  for (const Alfabeto& alfabeto : alfabetos) {
    std::cout << alfabeto;
  }
}
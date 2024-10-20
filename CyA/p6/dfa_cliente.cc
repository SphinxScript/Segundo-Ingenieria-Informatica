#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "alfabeto.h"
#include "cadena.h"
#include "transicion.h"
#include "dfa.h"


int main(int argc, char* argv[]) {
  system("clear");
  std::fstream inputfile{argv[1]};
  std::string linea_alfabeto;
  std::getline(inputfile, linea_alfabeto);
  Alfabeto alfabeto{linea_alfabeto};      //alfabeto del dfa
  std::string linea_estados;
  std::getline(inputfile, linea_estados);
  int numero_estados{std::stoi(linea_estados)};  //numero de estados del dfa
  std::string linea_estado_inicial;
  std::getline(inputfile, linea_estado_inicial);
  int estado_inicial = std::stoi(linea_estado_inicial);  //estado inicial del dfa
  std::string lineas_estados;
  Dfa dfa;
  while (std::getline(inputfile, lineas_estados)) {
    std::istringstream iss{lineas_estados};
    Estado estado_actual;       //objeto a crear estado actual
    int estado;
    iss >> estado;              //estado actual
    int aceptacion;
    iss >> aceptacion;          //estado de aceptacion
    int transiciones_del_estado;
    iss >> transiciones_del_estado;       //numero de transiciones del estado
    estado_actual = Estado{estado, aceptacion, transiciones_del_estado};
    std::string transiciones;
    std::getline(iss, transiciones);      //string con las transiciones del estado
    std::string transiciones_sin_espacios;
    estado_actual = Estado{estado, aceptacion, transiciones_del_estado};
    for (char c : transiciones) {
      if (c != ' ') {
        transiciones_sin_espacios += c;   //transiciones sin espacios
      }
    }
    Transicion transicion;
    for (int i{0}; i < static_cast<int>(transiciones_sin_espacios.size()) - 1; i += 2){
      int j = i + 1;
      char simbolo{transiciones_sin_espacios[i]};
      int estado_siguiente{transiciones_sin_espacios[j] - '0'};
      transicion = Transicion{simbolo, estado_siguiente};
      estado_actual.InsertTransicion(transicion);
    }
    std::cout << estado_actual << std::endl;
  }
  return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "alfabeto.h"
#include "cadena.h"
#include "estado.h"
#include "dfa.h"

void CreaDfa(const std::string& nombre_fichero, Dfa& dfa, Alfabeto& alfabeto) {
  std::fstream inputfile{nombre_fichero};
  std::string linea_alfabeto;
  std::getline(inputfile, linea_alfabeto);
  alfabeto = linea_alfabeto;      // alfabeto del dfa
  std::string linea_estados;
  std::getline(inputfile, linea_estados);
  int numero_estados{std::stoi(linea_estados)};  // número de estados del dfa
  std::string linea_estado_inicial;
  std::getline(inputfile, linea_estado_inicial);
  int estado_inicial = std::stoi(linea_estado_inicial);  // estado inicial del dfa
  std::string lineas_estados;
  std::map<int, Estado> estados;
  while (std::getline(inputfile, lineas_estados)) {
    std::istringstream iss{lineas_estados};
    Estado estado_actual;       // objeto a crear estado actual
    int estado;
    iss >> estado;              // estado actual
    if (estado > numero_estados || estado < 0) {
      std::cerr << "Error: el estado " << estado << " no es válido" << std::endl;
      exit(1);
    }
    int aceptacion;
    iss >> aceptacion;          // estado de aceptación
    if (aceptacion > numero_estados || aceptacion < 0) {
      std::cerr << "Error: el estado de aceptación no es válido" << std::endl;
      exit(1);
    }
    int transiciones_del_estado;
    iss >> transiciones_del_estado;       // número de transiciones del estado
    estado_actual = Estado{estado, aceptacion, transiciones_del_estado};
    std::string transiciones;
    std::getline(iss, transiciones);      // string con las transiciones del estado
    std::string transiciones_sin_espacios;
    estado_actual = Estado{estado, aceptacion, transiciones_del_estado};
    for (char c : transiciones) {
      if (c != ' ') {
        transiciones_sin_espacios += c;   // transiciones sin espacios
      }
    }
    for (int i{0}; i < static_cast<int>(transiciones_sin_espacios.size()) - 1; i += 2) {
      int j = i + 1;
      char simbolo{transiciones_sin_espacios[i]};
      if (!alfabeto.CheckSymbol(simbolo)) {
        std::cerr << "Error: el símbolo " << simbolo << " no pertenece al alfabeto" << std::endl;
        exit(1);
      }
      int estado_siguiente{transiciones_sin_espacios[j] - '0'};
      estado_actual.InsertTransicion(simbolo, estado_siguiente);
    }
    estados[estado] = estado_actual;
    // std::cout << estado_actual << std::endl;
  }
  dfa = Dfa{alfabeto, numero_estados, estado_inicial, estados};
}

std::vector<Cadena> VectorDeCadenas(const std::string& inputfile) {
  std::vector<Cadena> cadenas;
  std::ifstream file{inputfile};
  if (!file) {
    std::cerr << "Error: no se ha podido abrir el fichero" << std::endl;
    exit(1);
  }
  std::string cadena;
  while (std::getline(file, cadena)) {
    cadenas.push_back(Cadena{cadena});
  }
  return cadenas;
}

int main(int argc, char* argv[]) {
  system("clear");
  Dfa dfa;
  Alfabeto alfabeto;
  CreaDfa(argv[1], dfa, alfabeto);
  std::vector<Cadena> cadenas = VectorDeCadenas(argv[2]);
  // std::cout << dfa;
  dfa.ProcesarCadenas(cadenas);
  //std::cout << dfa;
  return 0;
}

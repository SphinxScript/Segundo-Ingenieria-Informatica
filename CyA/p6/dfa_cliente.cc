// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 17/10/2024
// Archivo: dfa_cliente.cc
// Contiene la implementación del programa cliente. Tanto main como funciones auxiliares.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <stack>

#include "alfabeto.h"
#include "cadena.h"
#include "estado.h"
#include "dfa.h"

bool usage(int argc) {
  bool correcto = true;
  if (argc != 3) {
    correcto = false;
    return correcto;
  }
  return correcto;
}

/**
 * @brief Esta función se encarga de crear el objeto Dfa a partir de un fichero de texto pasado como argumento.
 * @param nombre_fichero el nombre del fichero de texto que se le pasa a la función.
 * @param dfa el objeto Dfa que se va a crear.
 * @param alfabeto el alfabeto del dfa.
 * @return void
 */
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
    Estado estado_actual;       // objeto Estado a crear estado actual
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
  }
  dfa = Dfa{alfabeto, numero_estados, estado_inicial, estados};
}

/**
 * @brief Esta función se encarga de crear un vector de cadenas a partir de un fichero de texto pasado como argumento.
 * @param inputfile el nombre del fichero de texto que se le pasa a la función.
 * @return std::vector<Cadena> el vector de cadenas creado.
 */
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

// modificacion:
void DfaONfa(const Dfa& dfa, const Alfabeto& alfabeto) {
  std::map<int, Estado> estados = dfa.GetEstados();
  for (std::pair estado : estados) {
    Estado estado_actual = estado.second;
    if (estado_actual.GetNumeroTransiciones() > alfabeto.GetSize()) {
      std::cout << "Es NFA" << std::endl;
      break;
    }
    else {
      std::cout << "Es DFA" << std::endl;
      break;
    }
  }
}

/**
 * @brief Función principal main() del programa.
 * @param argc número de argumentos pasados al programa.
 * @param argv argumentos pasados al programa.
 * @return 0 si el programa se ha ejecutado correctamente.
 */
int main(int argc, char* argv[]) {
  system("clear");
  if (!usage(argc)) {
    std::cerr << "Error: el programa se debe ejecutar de la siguiente forma: " << std::endl;
    std::cerr << "./dfa_cliente <nombre_fichero> <nombre_fichero>" << std::endl;
    std::cerr << "El primer fichero debe contener la definición del dfa y el segundo las cadenas a procesar" << std::endl;
    return 1;
  }
  Dfa dfa;
  Alfabeto alfabeto;
  CreaDfa(argv[1], dfa, alfabeto);
  DfaONfa(dfa, alfabeto);
  std::vector<Cadena> cadenas = VectorDeCadenas(argv[2]);
  //std::cout << dfa;
  dfa.ProcesarCadenas(cadenas);
  //std::cout << dfa;
  return 0;
}

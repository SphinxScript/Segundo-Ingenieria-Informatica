/**
 * @file cliente_grammar2CNF.cc
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 01/11/2024
 * @brief Contiene el programa cliente que usará los métodos de la clase gramática y la práctica en sí
 * @version 1.0
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 8: Gramáticas en Forma Normal de Chomsky
 * 
 * @note
 * - 01/11/2024: Creación (primera versión) del código
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "gramatica.h"
#include "alfabeto.h"

/**
 * @brief: función que comprueba si la llamada al programa es correcta
 * @param[in] argc: el número de argumentos pasados al programa
 * @return true si la llamada es correcta, false en caso contrario
 */
bool Usage(int argc) {
  return ((argc != 3 && argc != 2) || argc < 3) ? false : true;
}

/**
 * @brief: función que comprueba si se ha pasado el argumento --help
 * @param[in] str: el string que se va a comprobar
 * @return true si el string es --help, false en caso contrario
 */
bool CompruebaHelp(const std::string& str) {
  bool help{false};
  if (str == "--help") help = true;
  return help;
}

/**
 * @brief: función que comprueba si la gramática pasada como parametro en fichero es válida
 * @param[in] input_file: el fichero de entrada
 * @return true si la gramática es válida, false en caso contrario
 */
bool CompruebaGramatica(std::ifstream& input_file) {
  bool valida = true;
  std::string linea;
  std::getline(input_file, linea);
  int terminales{std::stoi(linea)};
  for (int i{0}; i < terminales && std::getline(input_file, linea); ++i) {}
  std::getline(input_file, linea);
  int no_terminales{std::stoi(linea)};
  for (int i{0}; i <= no_terminales && std::getline(input_file, linea); ++i) {}
  while (std::getline(input_file, linea)) {
    char no_terminal;
    std::string produccion;
    std::istringstream iss(linea);
    iss >> no_terminal >> produccion;
    if (produccion.size() == 1) {
      if (isupper(produccion[0]) || produccion[0] == '&') {
        valida = false;
      }
    }
  }
  return valida;
}

/**
 * @brief: función que crea el alfabeto de la gramática
 * @param[in] input_file: el fichero de entrada
 * @return el alfabeto de la gramática
 */
Alfabeto CreaAlfabeto(std::ifstream& input_file) {
  input_file.clear();                             // limpiamos los distintos marcadores de error del fichero
  input_file.seekg(0, std::ios::beg);             // movemos el puntero de lectura al principio del fichero
  Alfabeto alfabeto;
  std::string linea;
  std::getline(input_file, linea);
  int tamanio_alfabeto{std::stoi(linea)}; 
  for (int i{0}; i < tamanio_alfabeto && std::getline(input_file, linea); ++i) {
    alfabeto.AddSymbol(linea[0]);
  }
  return alfabeto;
}

/**
 * @brief: función que crea el conjunto de símbolos no terminales de la gramática
 * @param[in] input_file: el fichero de entrada
 * @param[in] simbolos_no_terminales: el conjunto de símbolos no terminales
 * @param[in] arranque: el símbolo de arranque
 * @return void
 */
void SimbolosNoTerminales(std::ifstream& input_file, std::set<std::string>& simbolos_no_terminales, char& arranque)  {
  // limpiamos los distintos marcadores de error del fichero. No hace falta mover el puntero
  // de lectura al principio del fichero ya que esta función se llama después de CreaAlfabeto() y seguimos leyendo el fichero a partir de ahí
  input_file.clear();
  std::string linea;
  std::getline(input_file, linea);
  int numero_terminales{std::stoi(linea)};
  for (int i{0}; i < numero_terminales && std::getline(input_file, linea); ++i) {
    if (i == 0) {
      arranque = linea[0];
    }
    simbolos_no_terminales.insert(std::string(1, linea[0]));
  }
}

/**
 * @brief: función que crea las producciones de la gramática
 * @param[in] input_file: el fichero de entrada
 * @return el multimap que contiene las producciones de la gramática
 */
std::multimap<std::string, std::string> CreaProducciones(std::ifstream& input_file) {
  // limpiamos los distintos marcadores de error del fichero. No hace falta mover el puntero de lectura al principio
  // del fichero ya que esta función se llama después de SimbolosNoTerminales() y seguimos leyendo el fichero a partir de ahí
  input_file.clear();
  std::multimap<std::string, std::string> producciones;   // multimap que contendrá las producciones de la gramática
  std::string linea;                          // string que contendrá cada línea del fichero
  std::getline(input_file, linea);            // leemos la primera línea del fichero que contiene el número de producciones
  while(std::getline(input_file, linea)) {
    std::istringstream iss(linea);             // creamos un flujo de entrada a partir de la línea
    std::string productor;                            // char que contendrá el símbolo no terminal
    std::string producido;                            // string que contendrá la producción
    iss >> productor >> producido;                    // leemos el productor y el producido
    producciones.insert(std::make_pair(productor, producido)); // insertamos la producción en el multimap
  }
  return producciones;
}

/**
 * @brief: función principal del programa
 * @param[in] argc: el número de argumentos pasados al programa
 * @param[in] argv: el array de argumentos pasados al programa
 * @return 0 si el programa se ha ejecutado correctamente, 1 en caso contrario
 */
int main(int argc, char* argv[]) {
  system("clear");
  if (!Usage(argc) || argc == 1) {
    std::cerr << "Error en la llamada al programa." << std::endl;
    std::cerr << "Uso: ./grammar2CNF_cliente <fichero_entrada> <fichero_salida>" << std::endl;
    std::cout << "Para más información, ./grammar2CNF_cliente --help" << std::endl;
    return 1;
  }
  if (CompruebaHelp(argv[1])) {
    std::cout << "Este programa convierte una gramática independiente de contexto en una gramática en forma normal de Chomsky." << std::endl;
    std::cout << "Uso: ./grammar2CNF_cliente <fichero_entrada> <fichero_salida>" << std::endl;
    std::cout << "El fichero de entrada debe contener la gramática a convertir, sin producciones inútiles, unitarias ni vacías" << std::endl;
    return 0;
  }
  std::ifstream input_file(argv[1]);
  if (!input_file.is_open()) {
    std::cerr << "Error al abrir el fichero" << std::endl;
    std::cerr << "Asegúrese de que está correctamente escrito" << std::endl;
    return 1;
  }
  if (!CompruebaGramatica(input_file)) {
    std::cerr << "Error en la gramática." << std::endl;
    std::cerr << "La gramática introducida no es válida. Hay alguna producción unitaria o vacía." << std::endl;
  }
  else {
    Alfabeto alfabeto = CreaAlfabeto(input_file);   // creamos el alfabeto de la gramatica
    std::set<std::string> simbolos_no_terminales;          // creamos el conjunto de simbolos no terminales
    char arranque;                                  // creamos el simbolo de arranque
    SimbolosNoTerminales(input_file, simbolos_no_terminales, arranque); // inicializo los simbolos no terminales y el de arranque
    std::multimap<std::string, std::string> producciones{CreaProducciones(input_file)}; // creamos las producciones de la gramatica
    Gramatica gramatica(alfabeto, arranque, simbolos_no_terminales, producciones); // creamos la gramatica
    Gramatica gramatica_cnf = gramatica.ConvierteCNF(); // convertimos la gramatica a CNF
    std::ofstream output_file(argv[2]); // creamos el fichero de salida
    output_file << gramatica_cnf; // escribimos la gramatica en el fichero de salida
  }
  return 0;
}
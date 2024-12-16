// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en c++
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 04/10/2024
// Archivo: cliente_regex.cc: programa cliente
// Contiene el programa cliente de la práctica.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 04/10/2024 - Creación (primera versión) del código

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#include "variables.h"
#include "bucles.h"
#include "comentarios_bloque.h"
#include "comentarios_linea.h"

/**
 * @brief método que comrpueba si el nº de parametros pasados al main son correctos
 * @param argc nº de parametros pasados al main.
 * @return usage devuelve true o false dependiendo del número.
 */

bool usage(const int& argc) {
  bool usage = true;
  if (argc != 3) {
    usage = false;
  }
  return usage;
}

/**
 * @brief función que busca las variables del fichero. A medida que lo hace las inserta en un vector de objetos variable
 * @param vector_variable vector de objetos variable
 * @param linea linea sobre la que se busca
 * @param contador contador para contar el nº de linea
 */
void EncuentraVariables(std::vector<Variables>& vector_variables, const std::string& linea, const int& contador) {
  std::regex expression{"\\bint\\s*[a-zA-Z]+\\s*=?\\s*\\d*\\s*;$|\\bdouble\\s*[a-zA-Z]+\\s*=?\\s*\\d*.?\\d*\\s*;$"};
  std::smatch matches;
  if (std::regex_search(linea, matches, expression)) {
    Variables variable{matches.str(), contador};
    vector_variables.push_back(variable);
  }
}

/**
 * @brief función que busca los bucles del fichero. A medida que lo hace las inserta en un vector de objetos Bucles
 * @param vector_bucles vector de objetos Bucles
 * @param linea linea sobre la que se busca
 * @param contador contador para contar el nº de linea
 */
void EncuentraBucles(std::vector<Bucles>& vector_bucles, const std::string& linea, const int& contador) {
  std::regex expresion{"\\bfor|\\bwhile"};
  std::smatch coincidencias;
  if (std::regex_search(linea, coincidencias, expresion)) {
    Bucles bucle{coincidencias.str(), contador};
    vector_bucles.push_back(bucle);
  }
}

/**
 * @brief función que busca el main. Si lo encuentra pone la variable booleana main pasada como referencia a true.
 * @param linea linea donde se busca la aparición del main
 * @param main variable booleana que almacena si hay o no main
 */
void EncuentraMain(const std::string& linea, bool& main) {
  std::regex expresion{"int main\\s*\\(\\)\\s*\\{|int main\\s*\\(\\s*int\\s+argc\\s*,\\s*char\\*\\s+argv\\[\\]\\)\\s*\\{"};
  if (std::regex_search(linea, expresion)) main = true;
}

/**
 * @brief función que busca los comentarios en linea del fichero. A medida que lo hace las inserta en un vector de objetos ComentariosLinea
 * @param vector_lineas vector de objetos ComentariosLinea
 * @param linea linea sobre la que se busca
 * @param contador contador para contar el nº de linea
 * @param comentario le pasamos el objeto ComentariosBloque que estamos analizando para comprobar si hay dos ocurrencias de "//" dentro de un comentario de bloque para así no añadirl como comentario de línea
 */
void EncuentraComentariosLinea(std::vector<ComentariosLinea>& vector_lineas, const std::string& linea, const int& contador, ComentariosBloque& comentario) {
  std::regex expresion{"\\s*\\/\\/.*"};
  std::smatch coincidencias;
  if (std::regex_search(linea, coincidencias, expresion) && !comentario.GetInicio()) {
    ComentariosLinea comentario{coincidencias.str(), contador};
    vector_lineas.push_back(comentario);
  }
}

/**
 * @brief función que desempeña el programa principal, llamando a las diferentes funciones.
 * @param argc número de parámetros pasado como argumentos al main
 * @param argv array de caracteres pasado como argumentos al main
 */
void Programa(int argc, char* argv[]) {
  std::ifstream input_file{argv[1]};
  std::string linea;
  std::vector<Variables> vector_variables;
  std::vector<Bucles> vector_bucles;
  bool main{false};
  std::vector<ComentariosBloque> vector_comentarios;
  ComentariosBloque comentario;
  std::vector<ComentariosLinea> vector_comentarios_linea;
  int contador{1};
  while (std::getline(input_file, linea)) {
    EncuentraVariables(vector_variables, linea, contador);
    EncuentraBucles(vector_bucles, linea, contador);
    EncuentraMain(linea, main);

    comentario.ProcesarLinea(linea, contador, contador);
    if (!comentario.GetInicio()) {
      if (!comentario.GetBloque().empty()) {
        vector_comentarios.push_back(comentario);
        comentario = ComentariosBloque();
      }
    }

    EncuentraComentariosLinea(vector_comentarios_linea, linea, contador, comentario);
    ++contador;
  }
  std::ofstream output_file{argv[2]};

  output_file << "PROGRAM: " << argv[1] << std::endl;
  output_file << "DESCRIPTION:" << std::endl;
  output_file << vector_comentarios[0];       // el primer comentario en bloque es la descripción

  output_file << "VARIABLES:" << std::endl;
  for (auto imprimir : vector_variables) {
  output_file << imprimir;
  }
  output_file << std::endl;

  output_file << "STATEMENTS:" << std::endl;
  for (auto imprimir : vector_bucles) {
    output_file << imprimir;
  }
  output_file << std::endl;

  output_file << "MAIN:" << std::endl;
  if (main) output_file << "True" << std::endl << std::endl;
  else output_file << "False" << std::endl << std::endl;

  output_file << "COMMENTS:" << std::endl;
  for (int i{0}; i < static_cast<int>(vector_comentarios.size()); ++i) {
    if (i == 0) {
      vector_comentarios[i].PrintIntervalo(output_file);
      output_file << " DESCRIPTION" << std::endl;
    }
    else {
      vector_comentarios[i].PrintIntervalo(output_file);
      output_file << " COMENTARIO DE BLOQUE" << std::endl;
    }
  }
  for (auto linea : vector_comentarios_linea) {
    output_file << linea;
  }
  input_file.close();
}


/**
 * @brief función main()
 * @param argc número de parametros pasados como argumento
 * @param argv array de caracteres
 * @return retorna 0 si se ejecuta correctamente
 */
int main(int argc, char* argv[]) {
  system("clear");
  if (!usage(argc)) {
    std::cout << "Modo de empleo: ./regex.oug filein.txt fileout.txt" << std::endl;
    std::cout << "Este programa analiza un fichero entrada (filein.txt) pasado como argumento en busca de variables declaradas en lineas," << std::endl;
    std::cout << "bucles for y while, la existencia de una función main y todos los comentarios tanto en bloque como en linea." << std::endl;
    std::cout << "Posteriormente imprime la salida usando un formato estandar en (fileout.txt), fichero pasado como argumento" << std::endl;
    return 1;
  }
  Programa(argc, argv);
  return 0;
}
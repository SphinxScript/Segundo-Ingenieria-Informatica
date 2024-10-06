#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#include "variables.h"
#include "bucles.h"
#include "comentarios_bloque.h"
#include "comentarios_linea.h"

bool usage(const int& argc) {
  bool usage = true;
  if (argc != 3 && argc != 2) {
    usage = false;
  }
  return usage;
}

void EncuentraVariables(std::vector<Variables>& vector_variables, const std::string& linea, const int& contador) {
  std::regex expression{"\\bint\\s*[a-zA-Z]+\\s*=?\\s*\\d*\\s*;$|\\bdouble\\s*[a-zA-Z]+\\s*=?\\s*\\d*.?\\d*\\s*;$"};
  std::smatch matches;
  if (std::regex_search(linea, matches, expression)) {
    Variables variable{matches.str(), contador};
    vector_variables.push_back(variable);
  }
}

void EncuentraBucles(std::vector<Bucles>& vector_bucles, const std::string& linea, const int& contador) {
  std::regex expresion{"\\bfor|\\bwhile"};
  std::smatch coincidencias;
  if (std::regex_search(linea, coincidencias, expresion)) {
    Bucles bucle{coincidencias.str(), contador};
    vector_bucles.push_back(bucle);
  }
}

void EncuentraMain(const std::string& linea, bool& main) {
  std::regex expresion{"int main\\s*\\(\\)\\s*\\{|int main\\s*\\(\\s*int\\s+argc\\s*,\\s*char\\*\\s+argv\\[\\]\\)\\s*\\{"};
  if (std::regex_search(linea, expresion)) main = true;
}

void EncuentraComentariosLinea(std::vector<ComentariosLinea>& vector_lineas, const std::string& linea, const int& contador) {
  std::regex expresion{"^\\s*\\/\\/.*"};
  std::smatch coincidencias;
  if (std::regex_search(linea, coincidencias, expresion)) {
    ComentariosLinea comentario{coincidencias.str(), contador};
    vector_lineas.push_back(comentario);
  }
}

int main(int argc, char* argv[]) {
  system("clear");
  if (!usage(argc)) {
    std::cout << "Modo de empleo: ./regex.oug filein.txt fileout.txt ... Pruebe ./p02_strings --help para más información." << std::endl;
    return 1;
  }
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

    EncuentraComentariosLinea(vector_comentarios_linea, linea, contador);
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
  return 0;
}
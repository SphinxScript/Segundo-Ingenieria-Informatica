#include "comentarios.h"


void Comentarios::ProcesarLinea(const std::string& linea, const int& numero) {
  std::regex inicio_bloque{"\\/\\*"};
  std::regex final_bloque{"\\*\\/"};
  if (!inicio_bloque_) {
    std::smatch coincidencias;
    if (std::regex_search(linea, coincidencias, inicio_bloque)){
      inicio_bloque_ = true;
      comentarios_bloque_.push_back(coincidencias[0].str());
    }
  }
  else {
    std::smatch coincidencias;
    if (std::regex_search(linea, coincidencias, final_bloque)) {
      inicio_bloque_ = false;
      comentarios_bloque_.push_back(coincidencias[0].str());
    }
    else {
    comentarios_bloque_.push_back(linea);
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Comentarios& otro) {
  std::vector<std::string> vector = otro.GetBloque();
  std::cout << "prueba ";
  for (int i{0}; i < vector.size(); ++i) {
    os << vector[i];
  }
}

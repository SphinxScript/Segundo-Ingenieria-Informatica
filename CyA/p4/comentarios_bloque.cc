#include "comentarios_bloque.h"


void ComentariosBloque::ProcesarLinea(const std::string& linea, const int& numero, const int& fin_bloque) {
  std::regex inicio_bloque{"\\/\\*"};
  std::regex final_bloque{"\\*\\/"};
  if (!inicio_bloque_) {
    std::smatch coincidencias;
    if (std::regex_search(linea, coincidencias, inicio_bloque)){
      inicio_bloque_ = true;
      comentarios_bloque_.push_back(coincidencias.str());
      indices_.push_back(numero);
    }
  }
  else {
    std::smatch coincidencias;
    if (std::regex_search(linea, coincidencias, final_bloque)) {
      inicio_bloque_ = false;
      comentarios_bloque_.push_back(coincidencias.str());
      indices_.push_back(fin_bloque);
    }
    else {
    comentarios_bloque_.push_back(linea);
    }
  }
}

void ComentariosBloque::PrintIntervalo(std::ostream& os) const {
  std::vector<int> indices{GetIndices()};
  os << "[Line " << indices[0] << "-" << indices[1] << "]";
}

std::ostream& operator<<(std::ostream& os, const ComentariosBloque& otro) {
  std::vector<std::string> vector{otro.GetBloque()};
  for (int i{0}; i < static_cast<int>(vector.size()); ++i) {
    os << vector[i] << std::endl;
  }
  os << std::endl;
  return os;
}

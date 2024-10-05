#include "bucles.h"


void Bucles::ProcesarLinea(const std::string& linea, const int& numero) {
  std::string target_s{linea};
  std::regex expresion{"for\\s*\\(.*\\)\\s*\\{$|while\\s*\\(.*\\)\\s*\\{$"};
  std::smatch coincidencias;
  std::regex_search(target_s, coincidencias, expresion);
  for (auto coincidencia : coincidencias) {
    bucles_.push_back(coincidencia);
    num_linea_.push_back(numero);
  }
}

std::ostream& operator<<(std::ostream& os, const Bucles& otro) {
  os << "STATEMENTS:" << std::endl;
  std::vector<std::string> bucles{otro.GetBucles()};
  std::vector<int> indices{otro.GetNum()};
  for (int i{0}; i < static_cast<int>(bucles.size()); ++i) {
    os << "[Linea: " << indices[i] << "] " << bucles[i] << std::endl;
  }
  return os;
}
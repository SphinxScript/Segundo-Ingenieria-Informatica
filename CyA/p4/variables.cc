#include "variables.h"


void Variables::ProcesarLinea(const std::string& linea, const int& numero) {
  std::string target_s{linea};
  std::regex expression{"int\\s*[a-zA-Z]+\\s*=?\\s*\\d*\\s*;$|double\\s*[a-zA-Z]+\\s*=?\\s*\\d*.?\\d*\\s*;$"};
  std::smatch matches;
  std::regex_search(target_s, matches, expression);
  for (auto match : matches) {
    variables_.push_back(match);
    num_linea_.push_back(numero);
  }
}

std::ostream& operator<<(std::ostream& os, const Variables& otro) {
  os << "VARIABLES:" << std::endl;
  std::vector<std::string> vector{otro.GetVars()};
  std::vector<int> indices{otro.GetNum()};
  for (int i{0}; i < static_cast<int>(vector.size()); ++i) {
    os << "[Linea: " << indices[i] << "] " << vector[i] << std::endl;
  }
  return os;
}
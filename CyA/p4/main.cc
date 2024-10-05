#include "main.h"


void Main::ProcesarLinea(const std::string& target) {
  std::regex expresion{"main\\s*\\(\\)|main\\(int\\s+argc,\\s*char\\s+argv\\*\\[\\]\\)"};
  if (std::regex_search(target, expresion)) {
    main_ = true;
  }
}

std::ostream& operator<<(std::ostream& os, const Main& imprimir) {
  os << "MAIN:" << std::endl;
  bool main{imprimir.Exist()};
  if (main) os << "True" << std::endl;
  else os << "False" << std::endl;
  return os;
}
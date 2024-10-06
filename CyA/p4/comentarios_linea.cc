#include "comentarios_linea.h"

std::ostream& operator<<(std::ostream& os, const ComentariosLinea& otro) {
  os << "[Line " << otro.GetIndice() << "] " << otro.GetLinea() << std::endl;
  return os;
}
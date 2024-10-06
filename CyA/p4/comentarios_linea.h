#ifndef COMENTARIOS_LINEA_H
#define COMENTARIOS_LINEA_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class ComentariosLinea {
 public:
  ComentariosLinea() = default;
  ComentariosLinea(const std::string& linea, const int& indice) : linea_{linea}, indice_{indice} {};
  std::string GetLinea() const { return linea_; }
  int GetIndice() const { return indice_; }
 private:
  std::string linea_;
  int indice_;
};
std::ostream& operator<<(std::ostream& os, const ComentariosLinea& otro);

#endif
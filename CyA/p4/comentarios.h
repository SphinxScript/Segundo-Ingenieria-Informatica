#ifndef COMENTARIOS_H
#define COMENTARIOS_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Comentarios {
 public:
  Comentarios() = default;
  void ProcesarLinea(const std::string& linea, const int& numero);
  std::vector<std::string> GetBloque() const { return comentarios_bloque_; }
 private:
  bool inicio_bloque_{false};
  std::vector<std::string> comentarios_bloque_;
  std::vector<std::string> comentarios_linea_;
};
std::ostream& operator<<(std::ostream& os, const Comentarios& otro);


#endif
#ifndef COMENTARIOS_BLOQUE_H
#define COMENTARIOS_BLOQUE_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>

class ComentariosBloque {
 public:
  ComentariosBloque() = default;
  void ProcesarLinea(const std::string& linea, const int& numero, const int& fin_bloque);
  void PrintIntervalo(std::ostream& os) const;
  std::vector<std::string> GetBloque() const { return comentarios_bloque_; }
  std::vector<int> GetIndices() const { return indices_; }
  bool GetInicio() const { return inicio_bloque_; }
 private:
  bool inicio_bloque_{false};
  std::vector<std::string> comentarios_bloque_;
  std::vector<int> indices_;
};
std::ostream& operator<<(std::ostream& os, const ComentariosBloque& otro);



#endif
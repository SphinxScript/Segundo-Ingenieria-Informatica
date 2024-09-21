// Universidad de La Laguna
// Escuela Superior de Ingenier´ıa y Tecnolog´ıa
// Grado en Ingenier´ıa Inform´atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la funci´on main del proyecto que usa las clases X e Y
// para ... (indicar brevemente el objetivo)
// Referencias:
// Enlaces de inter´es

// Historial de revisiones
// 17/09/2024 - Creaci´on (primera versi´on) del c´odigo


#include "lenguaje.h"

Alfabeto::Alfabeto(const std::string& cadena) {
  for (char c : cadena) {
    alfabeto_.insert(c);
  }
}

std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto) {
  int contador{0};
  os << "{";
	for (const char& c : alfabeto.GetAlfabeto()) {
    os << c;
    ++contador;
    if (contador != alfabeto.GetSize()) {
      os << ", ";
    }
  }
  os << "}" << std::endl;
  return os;
}


Cadena::Cadena(const std::string& cadena) {
  cadena_ = cadena;
}

std::string Cadena::Inversa() const {
  std::string cadena{GetCadena()};
  std::string cadenaInvertida;
  cadenaInvertida.resize(cadena.size());
  int indice{static_cast<int>(cadena.size()) - 1};
  for (int i{0}; i < cadena.size(); ++i) {
    cadenaInvertida[indice] = cadena[i];
    --indice;
  }
  return cadenaInvertida;
}

std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  std::string cadenita = cadena.GetCadena();
  os << cadenita << std::endl;
  return os;
}

void Cadena::Longitud (std::ostream& os) const {
  std::string cadena{GetCadena()};
  os << cadena.size() << std::endl;
}

std::set<std::string> Cadena::Prefijos() const {
  std::set<std::string> conjuntoPrefijos;
  std::string cadena{GetCadena()};
  conjuntoPrefijos.insert("");
  for (int i{0}; i <= static_cast<int>(cadena.size()); ++i) {
    std::string subcadena;
    subcadena = cadena.substr(0, i);
    conjuntoPrefijos.insert(subcadena);
  }
  return conjuntoPrefijos;
}


std::set<std::string> Cadena::Sufijos() const {
  std::set<std::string> conjuntoSufijos;
  std::string cadena{GetCadena()};
  conjuntoSufijos.insert("");
  int indice{0};
  for (int i{static_cast<int>(cadena.size())}; i >= 0; --i) {
    std::string subcadena;
    subcadena = cadena.substr(i, indice);
    conjuntoSufijos.insert(subcadena);
    ++indice;
  }
  return conjuntoSufijos;
}
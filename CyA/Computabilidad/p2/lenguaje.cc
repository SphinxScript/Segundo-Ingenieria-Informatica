// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 19/09/2024
// Archivo: lenguaje.cc
// Contiene la implementación de los métodos de la clase Lenguaje
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#include "lenguaje.h"

// se emplea el constructor por defecto ya que se crea el objeto insertando cadenas en él.

/**
 * @brief método para insertar objetos cadena
 * @param cadena objeto cadena que se inserta en la clase Lenguaje.
 */
void Lenguaje::Insert(const Cadena& cadena) {
  Lenguaje_.insert(cadena);
}

/**
 * @brief método que modifica el Lenguaje que llama al método y crea a partir de él un Lenguaje de prefijos
 * @param cadena objeto cadena que se usará para los prefijos.
 */
void Lenguaje::LenguajePrefijos(const Cadena& cadena) {
  Cadena vacia{""};
  Insert(vacia);
  std::string copiaCadena = cadena.GetCadena();
  for (int i{0}; i <= static_cast<int>(cadena.Size()); ++i) {
    Cadena subcadena;
    std::string prefijo = copiaCadena.substr(0, i);
    subcadena = prefijo;
    Insert(subcadena);
  }
}

/**
 * @brief método que modifica el Lenguaje que llama al método y crea a partir de él un Lenguaje de sufijos
 * @param cadena objeto cadena que se usará para los sufijos.
 */
void Lenguaje::LenguajeSufijos(const Cadena& cadena) {
  Cadena vacia{""};
  Insert(vacia);
  std::string copiaCadena = cadena.GetCadena();
  int indice{0};
  for (int i{static_cast<int>(copiaCadena.size())}; i >= 0; --i) {
    Cadena subcadena;
    std::string sufijo = copiaCadena.substr(i, indice);
    subcadena = sufijo;
    Insert(subcadena);
    ++indice;
  }
}

/**
 * @brief sobrecarga para imprimir objetos Lenguaje
 * @param os flujo de salida
 * @param Lenguaje objeto Lenguaje que se imprimirá.
 * @return os retorna el flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Lenguaje& Lenguaje) {
  std::set<Cadena> cadenas = Lenguaje.GetLenguaje();
  os << "{";
  int contador{0};
  for (const auto& cadena : cadenas) {
    os << cadena;
    ++contador;
    if (contador != Lenguaje.Size()) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

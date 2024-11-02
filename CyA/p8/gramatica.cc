#include <iostream>
#include <vector>

#include "gramatica.h"

Gramatica Gramatica::ConvierteCNF() const {
  Gramatica gramatica = *this;

  std::set<std::string> simbolos_no_terminales{gramatica.GetSimbolosNoTerminales()};
  // multimap al que añadire las producciones en CNF
  std::multimap<std::string, std::string> producciones{gramatica.GetProducciones()};

  // primer bucle
  for (const std::pair<const std::string, std::string>& produccion : gramatica.GetProducciones()) {
    if (produccion.second.size() >= 2) {      // si lo producido tiene más de dos simbolos de tamaño:
      std::string produccion_aux{produccion.second};    // la parte derecha de la produccion
      int contador{0};
      for (int i{0}; i < static_cast<int>(produccion_aux.size()); ++i) {
        if (islower(produccion_aux[i])) {
          std::string productor{"C" + std::string(1, produccion_aux[i])};
          std::string producido{std::string(1, produccion_aux[i])};
          bool existe{false};     // para evitar que se inserten producciones repetidas usamos existe
          for (std::pair<const std::string, std::string>& produccion : producciones) {    // recorremos todo el multimap nuevo de producciones
            if (produccion.first == productor) {
              existe = true;
              break;
            }
          }
          if (!existe) {
            // std::cout << "Produccion: " << productor << " -> " << producido << std::endl;
            producciones.insert(std::make_pair(productor, producido));
          }
          simbolos_no_terminales.insert(productor);      // añadimos al conjunto de los no terminales el nuevo simbolo (para la nueva gramatica cnf)
          contador++;
        }
      }
    }
    else {
      producciones.insert(produccion);      // si no tiene más de 2 símbolos de tamaño, la produccion no se ve modificada por lo que se inserta tal cual
    }
  }


  for (const auto& produccion : producciones) {
    std::cout << produccion.first << " -> " << produccion.second << std::endl;
  }

  
  return gramatica;
}

std::ostream& operator<<(std::ostream& os, const Gramatica& gramatica) {
  os << "Alfabeto: " << gramatica.GetAlfabeto() << std::endl;
  os << "Simbolos no terminales: ";
  for (const std::string& no_terminal : gramatica.GetSimbolosNoTerminales()) {
    os << no_terminal << " ";
  }
  os << std::endl;
  os << "Arranque: " << gramatica.GetArranque() << std::endl;
  os << "Producciones: " << std::endl;
  for (const std::pair<const std::string, std::string>& produccion : gramatica.GetProducciones()) {
    os << produccion.first << " -> " << produccion.second << std::endl;
  }
  return os;
}
#include <iostream>
#include <vector>

#include "gramatica.h"

Gramatica Gramatica::ConvierteCNF() const {
  Gramatica gramatica{*this};         // copia de la gramática original

  // multimap que contendrá las producciones de la gramática
  std::multimap<std::string, std::string> producciones{gramatica.GetProducciones()};
  
  // creo una copia de las producciones para no modificar las originales
  std::multimap<std::string, std::string> producciones_cnf = producciones;

  // PRIMER BUCLE DEL ALGORITMO

  for (const std::pair<const std::string, std::string>& produccion : producciones) {
    std::string nueva_produccion = produccion.second;     // nueva_produccion es lo producido por el productor en producciones
    if (nueva_produccion.size() >= 2) {                   // comprobamos la produccion tiene al menos dos símbolos
      for (int i{0}; i < static_cast<int>(nueva_produccion.size()); ++i) {    // recorremos la produccion
        char simbolo{nueva_produccion[i]};                // simbolo es el iésimo simbolo de la produccion
        if (islower(simbolo)) {                           // si es terminal hacemos lo que procede
          std::string nuevo_productor = std::string{"C"} + simbolo;   // creamos un string con el nuevo productor Cx
          bool existe = false;                            // variable para identificar si el productor ya existe, para no repetirlo
          for (const std::pair<const std::string, std::string>& prod : producciones_cnf) {    // recorremos ahora todas las producciones del nuevo multimap que será la gramatica CNF
            if (prod.first == nuevo_productor) {          // si existe ya el productor en nuestro multimap, ponemos existe a true
              existe = true;
              break;
            }
          }
          if (!existe) {      // si no existe, insertamos en producciones_cnf el nuevo productor junto a su producción, que será el terminal
            producciones_cnf.insert(std::make_pair(std::string{nuevo_productor}, std::string(1, simbolo)));
          }
        }
      }
    }
  }
  // en este bucle sustituiré los terminales en las producciones por los productores que generan dichos terminales
  // ejemplo: si tenemos una producción S -> aB, como hemos añadido Ca -> a, entonces quedará S -> CaB
  for (std::pair<const std::string, std::string>& produccion : producciones_cnf) {
    std::string producido = produccion.second;
    if (producido.size() >= 2) {
      std::string nuevo_producido;
      for (char simbolo : producido) {
        if (islower(simbolo)) {  // Si es un terminal
          std::string no_terminal = "C" + std::string(1, simbolo);
          nuevo_producido += no_terminal;  // Añadimos el no terminal
        } else {
          nuevo_producido += simbolo;  // Añadimos el símbolo original
        }
      }
      produccion.second = nuevo_producido;  // Actualizamos la producción
    }
  }

  // SEGUNDO BUCLE DEL ALGORITMO


  for (const auto& produccion : producciones_cnf) {
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
/**
 * @file gramatica.cc
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 01/11/2024
 * @brief Contiene la implementación de los métodos de la clase Gramatica
 * @version 1.0
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 8: Gramáticas en Forma Normal de Chomsky
 * 
 * @note
 * - 01/11/2024: Creación (primera versión) del código
 */

#include <iostream>
#include <vector>

#include "gramatica.h"

/**
 * @brief: función que cuenta los símbolos de una producción
 * @param[in] produccion: la producción a contar
 * @return el número de símbolos de la producción
 */
int Gramatica::CuentaSimbolos(const std::string& produccion) const {
  int contador = 0;

  for (int i{0}; i < static_cast<int>(produccion.size()); ++i) {
    if (produccion[i] == 'C' && i + 1 < static_cast<int>(produccion.size()) && islower(produccion[i + 1])) {
      // Detectamos un símbolo del tipo "Cx", lo contamos como un solo símbolo
      ++contador;
      ++i;  // Avanzamos el índice para saltar el caracter que acompaña a 'C'
    }
    else {
      // Contamos cualquier otro símbolo de forma individual
      ++contador;
    }
  }

  return contador;
}

/**
 * @brief: función que crea el vector con los símbolos de una producción, empleada para contar, en el segundo bucle, los simbolos Cx
 * @param[in] produccion: la producción a convertir en vector
 * @return el vector con los símbolos de la producción
 */
std::vector<std::string> Gramatica::CreaVectorProduccion(const std::string& produccion) const {
  std::vector<std::string> vector_produccion;
  for (int i{0}; i < static_cast<int>(produccion.size()); ++i) {
    if (produccion[i] == 'C' && i + 1 < static_cast<int>(produccion.size()) && islower(produccion[i + 1])) {
      // Detectamos un símbolo del tipo "Cx", lo añadimos al vector
      vector_produccion.push_back(std::string{"C" + std::string(1, produccion[i + 1])});
      ++i;  // Avanzamos el índice para saltar el caracter que acompaña a 'C'
    }
    else {
      // Añadimos cualquier otro símbolo al vector
      vector_produccion.push_back(std::string{produccion[i]});
    }
  }
  return vector_produccion;
}

/**
 * @brief: función que crea los productores Dx... de una producción en el segundo bucle del algoritmo
 * @param[in] produccion: la producción a convertir en productores
 * @param[in] contador: el contador que lleva la cuenta de los productores D1, D2, ... Dn
 * @return el vector con los productores Dx...
 */
std::vector<std::string> Gramatica::CreaProductoresD(const std::string& produccion, int& contador) const {
  std::vector<std::string> productores_D;
  for (int i{0}; i < CuentaSimbolos(produccion) - 2; ++i) {
    productores_D.push_back(std::string{"D" + std::to_string(contador)});
    ++contador;
  }
  // for (const auto& productor : productores_D) {
  //   std::cout << productor;
  // }
  // std::cout << std::endl;
  return productores_D;
}

/**
 * @brief: función que convierte una gramática en forma normal de Chomsky
 * @return la gramática en forma normal de Chomsky
 */
Gramatica Gramatica::ConvierteCNF() const {
  Gramatica gramatica{*this};         // copia de la gramática original

  // multimap que contendrá las producciones de la gramática
  std::multimap<std::string, std::string> producciones{gramatica.GetProducciones()};
  
  // creo una copia de las producciones para no modificar las originales
  std::multimap<std::string, std::string> producciones_cnf = producciones;

  std::set<std::string> simbolos_no_terminales{gramatica.GetSimbolosNoTerminales()};  // conjunto de símbolos no terminales

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
            simbolos_no_terminales.insert(nuevo_productor);  // añadimos el nuevo productor al conjunto de símbolos no terminales
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

  std::multimap<std::string, std::string> producciones_cnf_copia = producciones_cnf;  // Copia de las producciones CNF
  producciones_cnf.clear();  // Limpiamos las producciones CNF
  int contador{1}; // contador para saber el indice de las producciones Dx...
  for (const std::pair<const std::string, std::string>& produccion : producciones_cnf_copia) {
    if (CuentaSimbolos(produccion.second) >= 3) {  // Si lo producido tiene al menos 3 símbolos
      std::vector<std::string> cadena_producidos{CreaVectorProduccion(produccion.second)};   // vector con la parte derecha de la produccion original (A1,A2, ..., An)
      std::vector<std::string> nuevos_productores{CreaProductoresD(produccion.second, contador)};  // Vector con (D1, D1, ..., D,)
      for (int i{0}; i < static_cast<int>(nuevos_productores.size()); ++i) {
        simbolos_no_terminales.insert(nuevos_productores[i]);  // Añadimos los nuevos productores al conjunto de símbolos no terminales
      }
      for (int i{0}; i < static_cast<int>(cadena_producidos.size()) - 1; ++i) {
        if (i == 0) {
          producciones_cnf.insert(std::make_pair(produccion.first, cadena_producidos[i] + nuevos_productores[i]));  // Añadimos la primera producción
        } else if (i == static_cast<int>(cadena_producidos.size()) - 2) {
          producciones_cnf.insert(std::make_pair(nuevos_productores[i - 1], cadena_producidos[i] + cadena_producidos[i + 1]));  // Añadimos la última producción correctamente
        } else {
          producciones_cnf.insert(std::make_pair(nuevos_productores[i - 1], cadena_producidos[i] + nuevos_productores[i]));  // Añadimos las producciones intermedias
        }
      }
    }
    else {
      producciones_cnf.insert(produccion);  // Si no tiene al menos 3 símbolos, la añadimos directamente
    }
  }
  // ahora actualizamos la gramatica con el mismo alfabeto, mismo simbolo de arranque, le pasamos los simbolos terminales actualizados
  // y las producciones actualizadas (producciones_cnf)
  gramatica = Gramatica(alfabeto_, arranque_, simbolos_no_terminales, producciones_cnf);  // Actualizamos la gramática original

  return gramatica;
}

std::ostream& operator<<(std::ostream& os, const Gramatica& gramatica) {
  os << "Alfabeto: " << gramatica.GetAlfabeto() << std::endl;
  os << "Simbolos no terminales: ";
  for (const std::string& no_terminal : gramatica.GetSimbolosNoTerminales()) {
    os << no_terminal << " ";
  }
  os << std::endl;
  os << "Arranque: " << gramatica.GetArranque() << std::endl << std::endl;
  os << "Producciones: " << std::endl;
  for (const std::pair<const std::string, std::string>& produccion : gramatica.GetProducciones()) {
    os << produccion.first << " -> " << produccion.second << std::endl;
  }
  return os;
}
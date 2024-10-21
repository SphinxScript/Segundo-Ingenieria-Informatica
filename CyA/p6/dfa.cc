#include "dfa.h"




Dfa::Dfa(const Alfabeto& alfabeto, int numero_estados, int estado_inicial, const std::map<int, Estado>& estados)
  : alfabeto_{alfabeto}, numero_estados_{numero_estados}, estado_inicial_{estado_inicial}, estados_{estados} {

}

std::set<Estado> Dfa::EpsilonClosure(const std::set<Estado>& estados) const {
  std::set<Estado> epsilon_cerradura;
  for (const Estado& estado : estados) {
    epsilon_cerradura.insert(estado);
  }
  return epsilon_cerradura;
}

bool Dfa::ValidarCadena(const std::string& cadena) const {
  // conjunto de estados actuales empezando en el estado inicial
  std::set<int> estados_actuales;
  estados_actuales.insert(estado_inicial_);  

  // procesamos cada simbolo de la cadena
  for (char c : cadena) {
    // Verificamos que el símbolo esta en el alfabeto o es el simbolo vacío '&'
    if (!alfabeto_.CheckSymbol(c) && c != '&') {
      return false;
    }

    // conjunto para almacenar los nuevos estados a los que podemos movernos
    std::set<int> nuevos_estados;
    
    // recorremos cada estado actual
    for (int estado : estados_actuales) {
      // obtenemos las transiciones del estado actual
      const std::multimap<char, int>& transiciones = estados_.at(estado).GetTransiciones();

      if (c == '&') {
        // Si el símbolo es '&', procesamos solo las epsilontransiciones
        std::pair<std::multimap<char, int>::const_iterator, std::multimap<char, int>::const_iterator> rango_epsilon = transiciones.equal_range('&');
        
        // Añadimos los estados a los que podemos transitar con epsilontransiciones
        for (std::multimap<char, int>::const_iterator it = rango_epsilon.first; it != rango_epsilon.second; ++it) {
          nuevos_estados.insert(it->second);
        }
      } else {
        // Procesamos las transiciones normales con el símbolo actual
        std::pair<std::multimap<char, int>::const_iterator, std::multimap<char, int>::const_iterator> rango = transiciones.equal_range(c);

        // Añadimos los estados a los que podemos transitar con el símbolo actual
        for (std::multimap<char, int>::const_iterator it = rango.first; it != rango.second; ++it) {
          nuevos_estados.insert(it->second);
        }
      }
    }

    // Si no hay nuevos estados y no procesamos ninguna transición epsilon, la cadena es rechazada
    if (nuevos_estados.empty()) {
      return false;
    }

    // Actualizamos el conjunto de estados actuales
    estados_actuales = nuevos_estados;
  }

  // Finalmente, verificamos si algún estado actual es un estado de aceptación
  for (int estado : estados_actuales) {
    if (estados_.at(estado).GetAceptacion() == 1) {
      return true;  // Si algún estado es de aceptación, la cadena es aceptada
    }
  }

  return false;  // Ningún estado de aceptación fue alcanzado
}


void Dfa::ProcesarCadenas(const std::vector<Cadena>& cadenas) const {
  for (const Cadena& cadena : cadenas) {
    if (ValidarCadena(cadena.GetCadena())) {
      std::cout << cadena.GetCadena() << " --- accepted" << std::endl;
    }
    else {
      std::cout << cadena.GetCadena() << " --- rejected" << std::endl;
    }
  }
}


std::ostream& operator<<(std::ostream& os, const Dfa& dfa) {
  os << "Alfabeto: " << dfa.GetAlfabeto();
  os << "Numero de estados: " << dfa.GetNumeroEstados() << std::endl;
  os << "Estado inicial: " << dfa.GetEstadoInicial() << std::endl << std::endl;
  for (const std::pair<int, const Estado>& estado : dfa.GetEstados()) {
    os << estado.first << " --> " << estado.second << std::endl;
  }
  return os;
}
#include "dfa.h"
#include <stack>



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

// funcion auxiliar para explorar todas las epsilontransiciones desde un conjunto de estados
std::set<int> Dfa::ExplorarEpsilonTransiciones(const std::set<int>& estados) const {
  std::set<int> estados_explorados = estados;  // comenzamos con los estados pasados
  std::stack<int> pila_estados;

  // metemos en la pila con todos los estados actuales
  for (int estado : estados) {
    pila_estados.push(estado);
  }

  // procesamos cada estado de la pila
  while (!pila_estados.empty()) {
    int estado_actual = pila_estados.top();
    pila_estados.pop();

    // obtenemos las transiciones epsilon ('&') del estado actual
    const std::multimap<char, int>& transiciones = estados_.at(estado_actual).GetTransiciones();
    std::pair<std::multimap<char, int>::const_iterator, std::multimap<char, int>::const_iterator> rango_epsilon = transiciones.equal_range('&');

    // para cada epsilontransicion
    for (std::multimap<char, int>::const_iterator it = rango_epsilon.first; it != rango_epsilon.second; ++it) {
      int nuevo_estado = it->second;

      // si el estado aun no ha sido explorado, lo añadimos y seguimos explorando desde el
      if (estados_explorados.find(nuevo_estado) == estados_explorados.end()) {
        estados_explorados.insert(nuevo_estado);
        pila_estados.push(nuevo_estado);
      }
    }
  }

  return estados_explorados;  // devuelve todos los estados alcanzados a traves de epsilontransiciones
}

bool Dfa::ValidarCadena(const std::string& cadena) const {
  // conjunto de estados actuales, comenzamos en el estado inicial
  std::set<int> estados_actuales;
  estados_actuales.insert(estado_inicial_);  // el estado inicial es el punto de partida

  // primero exploramos todas las epsilontransiciones desde el estado inicial
  estados_actuales = ExplorarEpsilonTransiciones(estados_actuales);

  // si la cadena es solo el simbolo '&', verificamos las epsilontransiciones
  if (cadena == "&") {
    // verificar si algun estado alcanzado es de aceptacion
    for (int estado : estados_actuales) {
      if (estados_.at(estado).GetAceptacion() == 1) {
        return true;
      }
    }
    return false;  // si no encontramos un estado de aceptacion, rechazamos la cadena
  }

  // procesamos cada simbolo de la cadena normal
  for (char c : cadena) {
    // verificamos que el simbolo esta en el alfabeto o es el simbolo vacio '&'
    if (!alfabeto_.CheckSymbol(c) && c != '&') {
      return false;  // si hay un simbolo que no esta en el alfabeto y no es '&', la cadena es rechazada
    }

    // conjunto para almacenar los nuevos estados a los que podemos movernos
    std::set<int> nuevos_estados;
    
    // recorremos cada estado actual
    for (int estado : estados_actuales) {
      // obtenemos las transiciones del estado actual
      const std::multimap<char, int>& transiciones = estados_.at(estado).GetTransiciones();

      if (c == '&') {
        // si el simbolo es '&', procesamos solo las epsilontransiciones
        std::pair<std::multimap<char, int>::const_iterator, std::multimap<char, int>::const_iterator> rango_epsilon = transiciones.equal_range('&');
        
        // añadimos los estados a los que podemos transitar con epsilontransiciones
        for (std::multimap<char, int>::const_iterator it = rango_epsilon.first; it != rango_epsilon.second; ++it) {
          nuevos_estados.insert(it->second);
        }
      } else {
        // procesamos las transiciones normales con el simbolo actual
        std::pair<std::multimap<char, int>::const_iterator, std::multimap<char, int>::const_iterator> rango = transiciones.equal_range(c);

        // añadimos los estados a los que podemos transitar con el simbolo actual
        for (std::multimap<char, int>::const_iterator it = rango.first; it != rango.second; ++it) {
          nuevos_estados.insert(it->second);
        }
      }
    }

    // si no hay nuevos estados y no procesamos ninguna transicion epsilon, la cadena es rechazada
    if (nuevos_estados.empty()) {
      return false;
    }

    // actualizamos el conjunto de estados actuales
    estados_actuales = ExplorarEpsilonTransiciones(nuevos_estados);
  }

  // finalmente verificamos si algun estado actual es un estado de aceptacion
  for (int estado : estados_actuales) {
    if (estados_.at(estado).GetAceptacion() == 1) {
      return true;  // si algun estado es de aceptacion, la cadena es aceptada
    }
  }

  return false;  // ningun estado de aceptacion fue alcanzado
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
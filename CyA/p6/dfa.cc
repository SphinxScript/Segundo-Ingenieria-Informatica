// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Ricardo David Rodríguez Pane
// Correo: alu0101643137@ull.edu.es
// Fecha: 17/10/2024
// Archivo: dfa.cc
// Contiene la implementacin de los metodos de la clase dfa
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 17/09/2024 - Creación (primera versión) del código

#include "dfa.h"
#include <stack>


/**
 * @brief Constructor de la clase Dfa
 * @param alfabeto Alfabeto del automata
 * @param numero_estados Numero de estados del automata
 * @param estado_inicial Estado inicial del automata
 * @param estados Estados del automata
 */
Dfa::Dfa(const Alfabeto& alfabeto, int numero_estados, int estado_inicial, const std::map<int, Estado>& estados)
  : alfabeto_{alfabeto}, numero_estados_{numero_estados}, estado_inicial_{estado_inicial}, estados_{estados} {

}



/**
 * @brief Funcion auxiliar para explorar todas las epsilontransiciones desde un conjunto de estados.
 *        Trabaja con una pila de estados para explorar todos los estados alcanzables a traves de epsilontransiciones.
 * @param estados Conjunto de estados desde los que explorar las epsilontransiciones
 * @return Conjunto de estados alcanzados a traves de epsilontransiciones
 */
std::set<int> Dfa::EpsilonClausura(const std::set<int>& estados) const {
  std::set<int> estados_explorados = estados;  // iniciamos un set<int> "estados_explorados" con los estados pasados como argumento
  std::stack<int> pila_estados;                // pila para ir explorando los estados alcanzables a traves de epsilontransiciones

  // metemos en la pila todos los estados actuales
  for (int estado : estados) {
    pila_estados.push(estado);
  }

  // procesamos cada estado de la pila mientras no se vacíe
  while (!pila_estados.empty()) {
    // estado actual (top de la pila) tipo entero
    int estado_actual = pila_estados.top();
    // sacamos el estado de la pila ya que se va a procesar
    pila_estados.pop();
      /*
        creamos un multimap<char, int> (char es el simbolo, int es el estado al que transita) a partir del estado actual 
        estados_at(estado_actual) devuelve el valor de la clave (el objeto Estado) asociado con la clave (nuestro estado actual)
        GetTransiciones() devuelve el multimapa<char, int> de las transiciones del estado
     */
    const std::multimap<char, int>& transiciones = estados_.at(estado_actual).GetTransiciones();

    // ahora declaramos un objeto pair de iteradores constantes para recorrer el multimapa (transiciones del estado actual)
    // como queremos saber las epsilontransiciones, buscamos el simbolo '&' como clave.
    // declaramos un std::pair de iteradores, donde el primer iterador apunta al primer elemento con clave '&' y el segundo al final de la secuencia
    std::pair<std::multimap<char, int>::const_iterator, std::multimap<char, int>::const_iterator> rango_epsilon = transiciones.equal_range('&');

    // ahora hariamos un bucle, recorriendo todo el rango de epsilontransiciones del estado actual
    // declaramos un multimap<char, int>::const_iterator iterador para recorrer el rango de epsilontransiciones
    // iteramos desde el primer iterador hasta el segundo, que marca el final del rango de las epsilontransiciones de nestro estado
    for (std::multimap<char, int>::const_iterator iterador = rango_epsilon.first; iterador != rango_epsilon.second; ++iterador) {
      // declaramos un entero "nuevo_estado" que guarda el primer estado (va avanzando en el bucle)
      // al que transita el estado actual con la epsilontransicion
      int nuevo_estado = iterador->second;

      // si el estado aun no ha sido explorado (se busca en el set "estados_explorados")
      // se añade a "estados_explorados" y a la pila de estados para explorar sus epsilontransiciones
      if (estados_explorados.find(nuevo_estado) == estados_explorados.end()) {
        estados_explorados.insert(nuevo_estado);
        pila_estados.push(nuevo_estado);
      }
    }
  }
  // finalmente cuando la pila se vacía, se retorna el set<int> estados_explorados, que contiene
  // todos los estados alcanzados mediante epsilontransiciones

  return estados_explorados;
}


/**
 * @brief Funcion para validar una cadena en el automata. Comprueba si la cadena es aceptada por el automata.
 *        Revisar los comentarios en linea a lo largo de la función para comprender su funcionamiento.
 * @param cadena Cadena a validar
 * @return true si la cadena es aceptada, false en caso contrario
 */
bool Dfa::ValidarCadena(const std::string& cadena) const {
  // declaramos un std::set<int> "estados_actuales" para almacenar los estados actuales
  std::set<int> estados_actuales;
  // insertamos el estado inicial en el set de estados actuales
  estados_actuales.insert(estado_inicial_);

  // primero exploramos todas las epsilontransiciones desde el estado inicial
  // y todos los alcanzados (incluido el estado inicial) se añaden a "estados_actuales"
  estados_actuales = EpsilonClausura(estados_actuales);

  // ahora procesamos cada simbolo de la cadena normal, ignorando ocurrencias de '&' en la cadena ya que es la cadena vacia
  for (char c : cadena) {
    if (c == '&') {
      continue;  // ignoramos el simbolo '&' en la cadena ya que representa la cadena vacia
    }

    // verificamos que el simbolo esta en el alfabeto
    if (!alfabeto_.CheckSymbol(c)) {
      return false;  // si hay un simbolo que no esta en el alfabeto, la cadena es rechazada directamente
    }

    // declaramos un set<int> "nuevos_estados" para almacenar los nuevos estados a los que podemos movernos
    // desde el actual
    std::set<int> nuevos_estados;

    // recorremos cada estado actual
    for (int estado : estados_actuales) {
      // obtenemos las transiciones del estado actual y las almacenamos en un multimap<char, int>
      // ya que el estado puede tener varias transiciones con el mismo simbolo (multimap<char, int>)
      const std::multimap<char, int>& transiciones = estados_.at(estado).GetTransiciones();

      // procesamos las transiciones con el simbolo "c" actual de la misma manera que con las epsilontransiciones
      // el metodo equal_range devuelve un pair de iteradores constantes que marcan el rango de transiciones con el simbolo "c" como clave
      // el primer iterador apunta al primer elemento del multimap con clave "c" y el segundo al siguiente después del último elemento
      // con el simbolo "c" como clave
      std::pair<std::multimap<char, int>::const_iterator, std::multimap<char, int>::const_iterator> rango = transiciones.equal_range(c);

      // ahora recorremos todas esas transiciones cuya clave es "c" y añadimos los estados a los que transitan al set "nuevos_estados"
      for (std::multimap<char, int>::const_iterator it = rango.first; it != rango.second; ++it) {
        // it es el iterador, por lo que apunta a un elemento del multimapa de transiciones de nuestro estado actual
        // it->second es el valor del estado al que lleva la transicion con el simbolo "c"
        nuevos_estados.insert(it->second);
      }
    }

    // dado que vamos insertando en nuevos_estados los estados a los que vamos accediendo, si nuevos_estados esta vacio
    // significa que no hay estados alcanzables con el simbolo "c" desde los estados actuales, por lo que la cadena es rechazada
    if (nuevos_estados.empty()) {
      return false;
    }

    // realizamos la epsilonclausura de los estados a los que llegamos desde los estados actuales ("nuevos_estados") con el simbolo "c"
    // y almacenamos los estados alcanzados con epsilon-clausuras en "estados_actuales"
    estados_actuales = EpsilonClausura(nuevos_estados);
  }

  // finalmente verificamos si algun estado actual del conjunto es un estado de aceptacion
  for (int estado : estados_actuales) {
    if (estados_.at(estado).GetAceptacion() == 1) {
      return true;  // si algun estado es de aceptacion, la cadena es aceptada
    }
  }

  return false;  // ningun estado de aceptacion fue alcanzado
}


/**
 * @brief Funcion para procesar un conjunto de cadenas en el automata. Imprime si cada cadena es aceptada o rechazada.
 * @param cadenas Conjunto de cadenas a procesar
 * @return void
 */
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

/**
 * @brief Sobrecarga del operador de insercion para la clase Dfa
 * @param os Flujo de salida
 * @param dfa Automata a imprimir
 * @return Flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const Dfa& dfa) {
  os << "Alfabeto: " << dfa.GetAlfabeto();
  os << "Numero de estados: " << dfa.GetNumeroEstados() << std::endl;
  os << "Estado inicial: " << dfa.GetEstadoInicial() << std::endl << std::endl;
  for (const std::pair<const int, Estado>& estado : dfa.GetEstados()) {
    os << estado.first << " --> " << estado.second << std::endl;
  }
  return os;
}
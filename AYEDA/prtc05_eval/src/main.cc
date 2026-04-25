#include "selection_sort_traza.h"
#include "sequence.h"
#include "bubble_sort_traza.h"
#include "mergesort_traza.h"
#include "heapsort_traza.h"
#include "shell_sort_traza.h"
#include "funciones.h"
#include "nif.h"
#include "sortmethod.h"



#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
  ArgsConfig configuracion;
  int argumentos = ManageArgs(argc, argv, configuracion);
  if (argumentos != 0) {
    if (argumentos == 1) {
      std::cout << "Error en los argumentos\n";
    }
    if (argumentos == 2) {
      std::cout << "No se ha especificado la opción -hash close \n";
    }
    if (argumentos == 3) {
      std::cout << "No se ha especificado la funcion de exploracion -fe <f>\n";
    }
    if (argumentos == 4) {
      std::cout << "No se ha especificado el tamaño de bloque -bs <s>\n";
    }
    std::cerr << "debug: aqui se ha producido un error en la gestión de argumentos\n";
    PrintHelp();
    return 1;
  }
  SortMethod<Nif>* metodo_ordenacion;
  StaticSeq<Nif> secuencia(configuracion.tablesize);
  switch (configuracion.init) {
    case 'm': {
      std::cout << "Generando secuencia manualmente...\n";
      std::cout << "Introuzca los nif 1 a 1 pulsando enter" << std::endl;
      unsigned count = 0;
      while (count < configuracion.tablesize) {
        std::string input;
        std::cin >> input;
        if (!CheckNumber(input)) {
          std::cout << "Entrada no válida. Por favor, introduzca un número o 'done' para finalizar.\n";
          continue;
        }
        Nif nif(std::stol(input));
        // Aquí se podría insertar el NIF en la secuencia o tabla hash según sea necesario
        secuencia[count] = nif; // Ejemplo de inserción en la secuencia
        ++count;
      }
      break;
    }
    case 'r': {
      std::cout << "Generando secuencia aleatoria...\n";
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<long> dis(10000000, 99999999);
      for (unsigned i = 0; i < configuracion.tablesize; ++i) {
        Nif nif(dis(gen));
        secuencia[i] = nif; // Ejemplo de inserción en la secuencia
      }
      break;
    }
    case 'f': {
      std::cout << "Generando secuencia de fichero...\n";
      std::string file_name = configuracion.fichero;
      unsigned size = configuracion.tablesize;

      std::ifstream input_file(file_name);
      if (!input_file.is_open()) {
        std::cerr << "Error: no se pudo abrir el fichero '" << file_name << "'.\n";
        std::exit(EXIT_FAILURE);
      }
      long nif_value;
      unsigned index = 0;
      while (input_file >> nif_value && index < size) {
        secuencia[index] = Nif(nif_value);
        ++index;
      }

      if (index < size) {
        std::cerr << "Error: el fichero contiene menos NIFs que el tamaño indicado.\n";
        std::exit(EXIT_FAILURE);
      }

      if (input_file >> nif_value) {
        std::cerr << "Aviso: el fichero contiene más NIFs que el tamaño indicado. "
                    "Se ignorarán los restantes.\n";
      }
      break;
    }
    default:
      std::cerr << "Metodo de inicializacion no valido";
      return 1;
  }
  switch (configuracion.method) {
    case 's':
      std::cout << "Método de ordenación seleccionado: Selection Sort\n";
      metodo_ordenacion = new MethodSelection<Nif>(secuencia, configuracion.tablesize);
      break;
    case 'b':
      std::cout << "Método de ordenación seleccionado: Bubble Sort\n";
      metodo_ordenacion = new MethodBubble<Nif>(secuencia, configuracion.tablesize);
      break;
    case 'm':
      std::cout << "Método de ordenación seleccionado: Merge Sort\n";
      metodo_ordenacion = new MethodMerge<Nif>(secuencia, configuracion.tablesize);
      break;
    case 'h':
      std::cout << "Método de ordenación seleccionado: Heap Sort\n";
      metodo_ordenacion = new MethodHeap<Nif>(secuencia, configuracion.tablesize);
      break;
    case 'i':
      std::cout << "Método de ordenación seleccionado: Shell Sort\n";
      std::cout << "Introduzca el decremento alpha para el método de ordenación Shell: ";
      double alpha;
      std::cin >> alpha;
      if (alpha <= 0 || alpha >= 1) {
        std::cerr << "Valor de alpha no válido. Debe ser un número entre 0 y 1.";
        return 1;
      }
      metodo_ordenacion = new MethodShell<Nif>(secuencia, configuracion.tablesize, alpha);
      break;
    default:
      std::cerr << "Metodo de ordenacion no valido";
      return 1;
  }
  unsigned contador = 0;
  std::vector<unsigned> asignaciones;
  while (contador < 10) {
    metodo_ordenacion->Sort();
    asignaciones.push_back(metodo_ordenacion->GetAsignaciones());
    metodo_ordenacion->SetAsignacionesZero();
    ++contador;
  }
  //calculamos la media de asignaciones
  unsigned suma_asignaciones = 0;
  for (unsigned asignacion : asignaciones) {
    suma_asignaciones += asignacion;
  }
  double media_asignaciones = static_cast<double>(suma_asignaciones) / asignaciones.size();
  std::cout << "Media de asignaciones realizadas: " << media_asignaciones << std::endl;
  // std::cout << "Secuencia ordenada:\n";
  // std::cout << secuencia;
  delete metodo_ordenacion;
  return 0;
  
}
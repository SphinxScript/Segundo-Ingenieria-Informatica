
#include <iostream>

#include "nif.h"
#include "persona.h"
#include "dispersionfunction.h"
#include "explorationfunction.h"
#include "hashtable.h"
#include "sequence.h"
#include "funciones.h"


int main(int argc, char* argv[]) {
  system("clear");
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
    PrintHelp();
    return 1;
  }
  DispersionFunction<Persona>* funcion_dispersion;
  switch (configuracion.fd) {
    case 0:
      funcion_dispersion = new DfModule<Persona>(configuracion.tablesize);
      break;
    case 1:
      funcion_dispersion = new DfSum<Persona>(configuracion.tablesize);
      break;
    case 2:
      funcion_dispersion = new DfRandom<Persona>(configuracion.tablesize);
      break;
    default:
      std::cerr << "funcion de dispersion no valida";
      return 1;
  }
  
  if (configuracion.dispersion == 'c') {
    ExplorationFunction<Persona>* funcion_exploracion;

    switch (configuracion.fe) {
      case 0:
        funcion_exploracion = new LinearExploration<Persona>;
        break;
      case 1:
        funcion_exploracion = new SquareExploration<Persona>;
        break;
      case 2:
        funcion_exploracion = new DoubleDispersionExpl<Persona>(*funcion_dispersion);
        break;
      case 3:
        funcion_exploracion = new RehashingExploration<Persona>(configuracion.tablesize);
        break;
      default:
        std::cerr << "funcion de exploracion no valida";
        return 1;
    }
    HashTable<Persona> tabla_hash(configuracion.tablesize, *funcion_dispersion, *funcion_exploracion, configuracion.blocksize);
    Menu(tabla_hash);
    delete funcion_exploracion;
  }
  else {
    HashTable<Persona, DynamicSeq<Persona>> tabla_hash(configuracion.tablesize, *funcion_dispersion);
    Menu(tabla_hash);
  }
  delete funcion_dispersion;
  return 0;
}
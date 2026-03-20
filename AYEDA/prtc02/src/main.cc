
#include <iostream>

#include "nif.h"
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
  DispersionFunction<Nif>* funcion_dispersion;
  switch (configuracion.fd) {
    case 0:
      funcion_dispersion = new DfModule<Nif>(configuracion.tablesize);
      break;
    case 1:
      funcion_dispersion = new DfSum<Nif>(configuracion.tablesize);
      break;
    case 2:
      funcion_dispersion = new DfRandom<Nif>(configuracion.tablesize);
      break;
    default:
      std::cerr << "funcion de dispersion no valida";
      return 1;
  }
  
  if (configuracion.dispersion == 'c') {
    ExplorationFunction<Nif>* funcion_exploracion;

    switch (configuracion.fe) {
      case 0:
        funcion_exploracion = new LinearExploration<Nif>;
        break;
      case 1:
        funcion_exploracion = new SquareExploration<Nif>;
        break;
      case 2:
        funcion_exploracion = new DoubleDispersionExpl<Nif>(*funcion_dispersion);
        break;
      case 3:
        funcion_exploracion = new RehashingExploration<Nif>(configuracion.tablesize);
        break;
      default:
        std::cerr << "funcion de exploracion no valida";
        return 1;
    }
    HashTable<Nif> tabla_hash(configuracion.tablesize, *funcion_dispersion, *funcion_exploracion, configuracion.blocksize);
    Menu(tabla_hash);
    delete funcion_exploracion;
  }
  else {
    HashTable<Nif, DynamicSeq<Nif>> tabla_hash(configuracion.tablesize, *funcion_dispersion);
    Menu(tabla_hash);
  }
  delete funcion_dispersion;
  return 0;
}
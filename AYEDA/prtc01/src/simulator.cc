#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "simulator.h"
#include "tape/tape.h"


/**
 * @brief Constructor de la clase Simulator. Se encarga de leer el fichero de entrada, inicializar la rejilla y la hormiga, y establecer el estado inicial de la simulación.
 * @param fichero_entrada Nombre del fichero de entrada que contiene la configuración inicial de la simulación.
 * @param control Referencia a un booleano que se establece a true si la inicialización es exitosa, o a false si ocurre algún error durante la lectura del fichero o la configuración
 */
Simulator::Simulator(const std::string& fichero_entrada, bool& control) {

  std::ifstream flujo_entrada{fichero_entrada};
  if (!flujo_entrada.is_open()) {
    std::cerr << "No se ha podido abrir el fichero de entrada.\n";
    control = false;
    return;
  }
  // capturamos el tamaño de la rejilla
  int sizeX, sizeY;
  flujo_entrada >> sizeX >> sizeY;
  int num_colores;
  flujo_entrada >> num_colores;
  std::string hormigas_linea;
  std::getline(flujo_entrada, hormigas_linea);  // ahora estaria vacia porque quedó el retorno de carro
  std::getline(flujo_entrada, hormigas_linea);  // almacenamos la linea de las hormigas
  std::stringstream flujo_hormigas{hormigas_linea};

  // vector de colores ANSI para asignar a cada hormiga
  std::vector<std::string> coloresANSI = {
    "\033[31m", // rojo
    "\033[32m", // verde
    "\033[33m", // amarillo
    "\033[34m", // azul
    "\033[35m"  // magenta
  };
  int idx_color{0};
  int contador_hormigas{0};
  std::string hormiga_ind;
  while (std::getline(flujo_hormigas, hormiga_ind, ';')) {
    if (hormiga_ind.empty()) continue;
    std::stringstream flujo_individual{hormiga_ind};
    std::string reglas;
    int pos_x, pos_y, orientacion;
    if (!(flujo_individual >> reglas >> pos_x >> pos_y >> orientacion)) {
      std::cerr << "Error: formato incorrecto en la línea de las hormigas.\n";
      control = false;
      ClearAnts();
      return;
    }
    if (pos_x < 0 || pos_x >= sizeX || pos_y < 0 || pos_y >= sizeY) {
      std::cerr << "Error: posición de la hormiga fuera de los límites de la rejilla.\n";
      std::cerr << "Posición de la hormiga: (" << pos_x << ", " << pos_y << ")\n";
      control = false;
      ClearAnts();
      return;
    }
    if (idx_color >= static_cast<int>(coloresANSI.size())) idx_color = 0;
    Ant* hormiga = new AntReglas(reglas, coloresANSI[idx_color]);
    hormiga->SetPlace(pos_x, pos_y, orientacion);
    hormigas_.push_back(hormiga);
    ++idx_color;
    ++contador_hormigas;
  }

  rejilla_.SetSize(sizeX, sizeY);
  rejilla_.SetColores(num_colores);
  std::string linea;
  while (std::getline(flujo_entrada, linea)) {
    // cada linea es una posición de la rejilla que pasa de blanco (0) por defecto a negro(1)
    if (linea.empty()) continue;
    int x, y, color;
    std::stringstream flujo_linea{linea};
    flujo_linea >> x >> y >> color;    
    rejilla_.FlipColor(x, y, color);
  }
  control = true;
}

/**
 * @brief Destructor de la clase Simulator. Se encarga de liberar la memoria asignada a las hormigas.
 */
Simulator::~Simulator() {
  ClearAnts();
}


/**
 * @brief Ejecuta la simulación de Langton según la opción seleccionada.
 * @param opcion Opción de simulación (1 para paso a paso, otro valor para ejecución continua).
 * @return void
 */
void Simulator::Simulate(const int& opcion) {
  std::cout << "Presione enter para avanzar, cualquier otra tecla + enter para finalizar";  
  std::string input;
  bool paso_valido{true};
  int contador{0};
  while(paso_valido) {
    if (opcion == 1) {
      getline(std::cin, input);
      if (!input.empty()) break;
      else {
        paso_valido = Step(contador);
      }
    }
    else {
      paso_valido = Step(contador);
    }
  }
  std::cout << "finalizando simulación..." << std::endl;
}

/**
 * @brief Ejecuta un paso de la simulación, moviendo la hormiga y actualizando la rejilla.
 * @param contador Referencia a un contador que se incrementa en cada paso para llevar el seguimiento del número de pasos realizados.
 * @return true si el paso es válido (dentro de los límites de la rejilla), false si la hormiga se sale de la rejilla.
 */
bool Simulator::Step(int& contador) {
  for (int i{0}; i < static_cast<int>(hormigas_.size()); ++i) {
    bool ok = hormigas_[i]->Move(rejilla_);
    if (!ok) {
      std::cout << "La hormiga de color " << ColorHormiga(*hormigas_[i]) << " se ha salido de la rejilla. Finalizando simulación..." << std::endl;
      return false;
    }
  }
  system("clear");
  // imprimimos indices de columnas:
  std::cout << "    ";
  for (int i{0}; i < rejilla_.GetSize().second; ++i) {
    std::cout << i % 10 << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < rejilla_.GetSize().first; ++i) {
    std::cout << i % 10 << " | ";
    for (int j = 0; j < rejilla_.GetSize().second; ++j) {
      for (int k{0}; k < static_cast<int>(hormigas_.size()); ++k) {
        if (hormigas_[k]->GetPosition() == std::pair(i,j)) {
          std::cout << hormigas_[k]->GetColorANSI() << *hormigas_[k] << "\033[0m ";
          break;
        }
        else if (k == static_cast<int>(hormigas_.size()) - 1) {
          switch(rejilla_.GetMalla()[i][j]) {
            case Colores::c0:
              std::cout << "□ ";
              break;
            case Colores::c1:
              std::cout << "\033[34m■\033[0m ";  // azul oscuro
              break;
            case Colores::c2:
              std::cout << "\033[32m■\033[0m ";  // verde oscuro
              break;
            case Colores::c3:
              std::cout << "\033[31m■\033[0m ";  // rojo oscuro
              break;
            case Colores::c4:
              std::cout << "\033[33m■\033[0m ";  // amarillo oscuro
              break;
          }
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Paso " << contador << std::endl;
  ++contador;
  return true;
}

/**
 * @brief Sobrecarga del operador de salida para imprimir el estado actual del simulador, incluyendo la rejilla y la posición de las hormigas.
 * @param os Flujo de salida.
 * @param simulator Objeto Simulator que se desea imprimir.
 * @return Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Simulator& simulator) {
  os << "    ";
  for (int i{0}; i < simulator.rejilla_.GetSize().second; ++i) {
    os << i % 10 << " ";
  }
  os << std::endl;
  for (int i = 0; i < simulator.rejilla_.GetSize().first; ++i) {
    os << i % 10 << " | ";
    for (int j = 0; j < simulator.rejilla_.GetSize().second; ++j) {
      for (int k{0}; k < static_cast<int>(simulator.hormigas_.size()); ++k) {
        if (simulator.hormigas_[k]->GetPosition() == std::pair(i,j)) {
          os << simulator.hormigas_[k]->GetColorANSI() << *simulator.hormigas_[k] << "\033[0m ";
          break;
        }
        else if (k == static_cast<int>(simulator.hormigas_.size()) - 1) {
          switch(simulator.rejilla_.GetMalla()[i][j]) {
            case Colores::c0:
              os << "□ ";
              break;
            case Colores::c1:
              os << "\033[34m■\033[0m ";  // azul oscuro
              break;
            case Colores::c2:
              os << "\033[32m■\033[0m ";  // verde oscuro
              break;
            case Colores::c3:
              os << "\033[31m■\033[0m ";  // rojo oscuro
              break;
            case Colores::c4:
              os << "\033[33m■\033[0m ";  // amarillo oscuro
              break;
          }
        }
      }
    }
    os << std::endl;
  }
  return os;
}

std::string Simulator::ColorHormiga(const Ant& hormiga) const {
  std::string color;
  if (hormiga.GetColorANSI() == "\033[31m") color = "rojo";
  else if (hormiga.GetColorANSI() == "\033[32m") color = "verde";
  else if (hormiga.GetColorANSI() == "\033[33m") color = "amarillo";
  else if (hormiga.GetColorANSI() == "\033[34m") color = "azul";
  else if (hormiga.GetColorANSI() == "\033[35m") color = "magenta";
  return color;
}

/**
 * @brief Libera la memoria asignada a las hormigas y limpia el vector de hormigas.
 */
void Simulator::ClearAnts() {
  for (Ant* a : hormigas_) delete a;
  hormigas_.clear();
}
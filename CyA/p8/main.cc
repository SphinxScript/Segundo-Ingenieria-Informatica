#include <iostream>
#include <string>

int main() {
  system("clear");
  std::string cadena{"Holabby"};
  std::string cadena2{"ooo"};
  cadena.replace(1, 1, cadena2);
  std::cout << cadena << std::endl;
  return 0;
}
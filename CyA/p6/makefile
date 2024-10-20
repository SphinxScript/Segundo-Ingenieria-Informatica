CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = ejecutable.out
SOURCE = alfabeto.cc cadena.cc dfa_cliente.cc transicion.cc estado.cc dfa.cc

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
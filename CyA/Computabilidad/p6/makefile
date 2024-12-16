CXX = g++
CXXFLAGS = -std=c++23 -Wall
TARGET = ejecutable.out
SOURCE = alfabeto.cc cadena.cc dfa_cliente.cc estado.cc dfa.cc

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
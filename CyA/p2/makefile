CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = ejecutable.out
SOURCE = funciones.cc lenguaje.cc main.cc

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
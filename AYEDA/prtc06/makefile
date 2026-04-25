

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC_DIR = src
TARGET  = arbol.out

# Archivos fuente  (todo lo terminado en .cc en el directorio src)
SOURCES = $(shell find $(SRC_DIR) -name "*.cc")

# Regla por defecto
all: $(TARGET)

# Compilar y enlazar en un paso
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Limpiar
clean:
	rm -f $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) -ts 4 -fd 0 -hash close -fe 0 -bs 12
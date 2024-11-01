CXX = g++
CXXFLAGS = -std=c++23 -Wall
TARGET = gramaticaCNF_conversor.out
SOURCE = cliente_grammar2CNF.cc alfabeto.cc gramatica.cc

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
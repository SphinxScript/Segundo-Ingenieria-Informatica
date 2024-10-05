CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = regex.out
SOURCE = cliente_regex.cc variables.cc bucles.cc main.cc

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
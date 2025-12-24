PROJECT = lab1
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror
GTEST_LIBS = -lgtest -lgtest_main -pthread 
SRC = main.cpp BitmapImg.cpp tests.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(PROJECT)

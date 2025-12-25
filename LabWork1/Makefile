CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror
LDFLAGS = -lgtest -lgtest_main -pthread

SRC = main.cpp BitmapImg.cpp ImageProcessor.cpp
TEST_SRC = tests.cpp BitmapImg.cpp ImageProcessor.cpp

all: lab1 run_tests

lab1: $(SRC:.cpp=.o)
	$(CXX) -o $@ $^ $(LDFLAGS)

run_tests: $(TEST_SRC:.cpp=.o)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o lab1 run_tests

test: run_tests
	./run_tests
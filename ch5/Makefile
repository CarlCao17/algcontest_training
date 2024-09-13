CXX = g++
CXXFLAGS = -std=c++20

build:
	$(CXX) $(CXXFLAGS) $(filename).cpp -o $(filename)

run: build
	./$(filename) < $(filename).in > $(filename).out
	diff $(filename).out $(filename).ans
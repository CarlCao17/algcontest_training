CXX = g++
CXXFLAGS = -lm -O2 -std=c++11 -pipe -DONLINE_JUDGE

build:
	cd $(dir) && $(CXX) $(CXXFLAGS) $(filename).cpp -o $(filename)

run: build
	cd $(dir) && ./$(filename) < $(filename).in > $(filename).out
	cd $(dir) && diff $(filename).out $(filename).ans
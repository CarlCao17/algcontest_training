CXX = g++
CXXFLAGS = -lm -O2 -std=c++11 -pipe -DONLINE_JUDGE
BINPATH = ./bin

build:
	if [[ ! -d "$(BINPATH)/$(dir)" ]]; then mkdir -p "$(BINPATH)/$(dir)"; fi
	$(CXX) $(CXXFLAGS) "$(dir)/$(filename).cpp" -o "$(BINPATH)/$(dir)/$(filename)"

run: build
	"$(BINPATH)/$(dir)/$(filename)" < "$(dir)/$(filename).in" > "$(dir)/$(filename).out"
	diff "$(dir)/$(filename).out" "$(dir)/$(filename).ans"


.PHONY: clean
clean:
	find $(BINPATH) -type d -exec sh -c 'find {} -maxdepth 1 -type f -perm -u=x -delete;' \;
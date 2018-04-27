OBJECTS = $(patsubst src/%.cpp, src/%.o, $(wildcard src/*.cpp))
HEADERS = $(wildcard include/*.h) $(wildcard include/config_structs/*.h)

OUTPUT_DIR = bin/
EXE = a.exe

CXX = g++
CXXFLAGS = -Wall -std=c++11 -I./include/

.PHONY: clean run

program: $(OBJECTS) $(HEADERS)
	@$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(OUTPUT_DIR)$(EXE)

src/%.o: src/%.cpp $(HEADERS)
	@echo recompiling: $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: program
	@echo
	@echo "--RUNNING--"
	@./$(OUTPUT_DIR)$(EXE) bin/obj.idx bin/obj.dat

clean clear: 
	rm -f $(OBJECTS)

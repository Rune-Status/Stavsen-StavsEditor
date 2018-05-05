OBJECTS = $(patsubst src/%.cpp, src/.%.o, $(wildcard src/*.cpp))
HEADERS = $(wildcard include/*.h) $(wildcard include/ArchiveManager/*.h)

OUTPUT_DIR = bin/
LIB_NAME = stavseditor

CXX = g++
CXXFLAGS = -Wall -std=c++11 -I./include/

TEST_SOURCES = $(wildcard test/*.cpp)
TEST_HEADERS = $(wildcard test/*.h) 

TEST_EXE = test.exe
TEST_CXXFLAGS = -Wall -std=c++11 -I./include/

.PHONY: shared static test clean clear run

default: static

./src/.%.o: ./src/%.cpp $(HEADERS)
	@echo recompiling $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

static: $(OBJECTS)
	@ar rcs $(OUTPUT_DIR)lib$(LIB_NAME).a $(OBJECTS)

shared:
	@echo todo

test: static
	@$(CXX) $(TEST_CXXFLAGS) $(TEST_SOURCES) -L$(OUTPUT_DIR) -l$(LIB_NAME) -o $(OUTPUT_DIR)$(TEST_EXE)

run: test
	@echo 
	@echo --RUNNING TEST--
	@./$(OUTPUT_DIR)$(TEST_EXE)

clean clear: 
	rm -f $(OBJECTS)

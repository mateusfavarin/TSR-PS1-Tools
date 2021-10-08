CC = g++
FLAGS = -std=c++17
CPP_FILES = main.cpp extractor.cpp racer.cpp course.cpp raw.cpp
PROGRAM = extractor

all: $(CPP_FILES)
	@$(CC) $(FLAGS) $(CPP_FILES) -static -o $(PROGRAM)

test: $(CPP_FILES)
	@$(CC) $(FLAGS) $(CPP_FILES) -static -o $(PROGRAM)
	@.\$(PROGRAM).exe ../../GAME/

clean:
	@rm $(PROGRAM)
	@rm -rf Output/

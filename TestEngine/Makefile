COMPILER = g++
COPTIONS = -Wall -Wpedantic -O3 -fopenmp -std=c++11 -c
LINKER = g++
LOPTIONS = -lsfml-window -lsfml-system -lsfml-graphics -lgomp -lX11
OBJ = obj/
BIN = bin/

All: Debug

Debug: $(OBJ) $(BIN) $(OBJ)GraphField.o $(OBJ)test.o
	$(LINKER) $(OBJ)GraphField.o $(OBJ)test.o -o $(BIN)Cells $(LOPTIONS)

cleanDebug:
	rm $(OBJ)*.o

$(OBJ)GraphField.o: GraphField.cpp GraphField.h
	$(COMPILER) $(COPTIONS) GraphField.cpp -o $(OBJ)GraphField.o

$(OBJ)test.o: test.cpp GraphField.h
	$(COMPILER) $(COPTIONS) test.cpp -o $(OBJ)test.o

$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

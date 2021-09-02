C = gcc
CFLAGS = -Wall -g

OBJ = main.o kas.o
EXE = main

all: $(EXE)

$(EXE):	$(OBJ)
	$(C) -o $(EXE) $(OBJ)

main.o: main.c ../../compiled/kas.h
	$(C) -o $@ -c $< $(CFLAGS)
 
kas.o: ../../compiled/kas.c
	$(C) -o $@ -c $< $(CFLAGS)

clean:
	rm $(EXE)


C = gcc
CFLAGS = -Wall -g

OBJ = main.o kmlib.o
EXE = main

all: $(EXE)

$(EXE):	$(OBJ)
	$(C) -o $(EXE) $(OBJ)

main.o: main.c ../../compiled/kmlib.h
	$(C) -o $@ -c $< $(CFLAGS)
 
kmlib.o: ../../compiled/kmlib.c
	$(C) -o $@ -c $< $(CFLAGS)

clean:
	rm $(EXE)
	rm $(OBJ)


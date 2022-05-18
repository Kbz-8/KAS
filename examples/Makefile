C = gcc
CFLAGS = -std=gnu11 -w -g -I ../includes

OBJ = main.o
EXE = main

all: $(EXE)

$(EXE):	$(OBJ)
	@$(C) -o $(EXE) $(OBJ) ../build/kmlib.so
	@rm $(OBJ)

main.o: main.c
	@$(C) -o $@ -c $< $(CFLAGS)

clean:
	@rm $(EXE)

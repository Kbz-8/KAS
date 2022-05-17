C = gcc
CFLAGS = -std=gnu11 -w

DEBUG ?= no

ifeq ($(DEBUG), yes)
	CFLAGS += -g
endif

OBJ = main.o kmlib.o
EXE = main

all: $(EXE)

$(EXE):	$(OBJ)
	@$(C) -o $(EXE) $(OBJ)

main.o: main.c ../../compiled/kmlib.h
	@$(C) -o $@ -c $< $(CFLAGS)

kmlib.o: ../../compiled/kmlib.c
	@$(C) -o $@ -c $< $(CFLAGS)

ifeq ($(DEBUG), yes)
	@echo "\033[1;32m[debug build completed]\033[1;00m"
else
	@echo "\033[1;32m[release build completed]\033[1;00m"
endif

clean:
	rm $(EXE)
	rm $(OBJ)

# This file is a part of the kmlib (kbz_8 main library)
#
# Copyright (C) 2022 @kbz_8
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

C = gcc
CFLAGS = -std=gnu11

DEBUG ?= no
VERBOSE ?= no

ARCH := $(shell uname -m)

INCLUDEDIRS = -Iincludes -Isrc/arch/$(ARCH)
CFLAGS += $(INCLUDEDIRS)

ifeq ($(DEBUG), yes)
	CFLAGS += -g
endif

ifeq ($(VERBOSE), no)
	CFLAGS += -w
endif

SRC = $(wildcard $(addsuffix /*.c, ./src))
SRC += $(wildcard $(addsuffix /*.c, ./src/sys))
SRC += $(wildcard $(addsuffix /*.c, ./src/arch/$(ARCH)))

BUILD_DIR = ./build

OBJ = $(SRC:.c=.o)

RES = $(BUILD_DIR)/kmlib.so

all: $(RES)

$(RES):	$(OBJ)
	@[ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR)
	@$(C) -shared -o $(RES) $(OBJ) -lrt
	@rm $(OBJ)
	@echo "\033[1;32m[build finished]\033[1;00m"

%.o: %.c
	@echo "\033[1;32m[compiling]\033[1;00m "$<
	@$(C) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(BUILD_DIR)

# -*- Mode: makefile; -*-

# Copyright (C) 2015 Alexey Veretennikov (alexey dot veretennikov at gmail.com)
# 
#	This file is part of libkv.
#
# libkv is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libkv is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with libkv.  If not, see <http://www.gnu.org/licenses/>.

ifeq ($(CC),cc)
	override CC = gcc
endif
LEX = flex
YACC = bison

INCLUDES = -I . -I src
CFLAGS = -ggdb -pg --std=c99 -pedantic -Wall -Wextra -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wdeclaration-after-statement -Wmissing-declarations $(INCLUDES)
LINKFLAGS = -L. -lkv

OUTPUT_SRC = testsrc/main.c
SOURCES := $(wildcard src/*.c) $(wildcard testsrc/*.c)
HEADERS := $(wildcard src/*.h) $(wildcard testsrc/*.h)
LEXES   := $(wildcard src/*.lex)
OBJECTS := libkv.yy.o libkv.tab.o $(patsubst %.c,%.o,$(SOURCES)) 
OBJECTS_LIB := $(filter-out $(patsubst %.c,%.o,$(OUTPUT_SRC)),$(OBJECTS))
OUTPUT = kvtest
OUTPUT_LIB = libkv.a

.PHONY: all clean

all: $(OUTPUT)

%.o : %.c %.h
	$(CC) -c $(CFLAGS) $(DEFINES) $(INCLUDES) $< -o $@

libkv.tab.o: libkv.tab.c libkv.tab.h
	$(CC) -c -ggdb -pg $(INCLUDES) -o $@ $<

libkv.tab.h: src/grammar.y libkv.tab.c

libkv.tab.c: src/grammar.y
	$(YACC) -y --defines=libkv.tab.h -o $@ $<

libkv.yy.o: libkv.yy.c libkv.tab.c
	$(CC) -c -ggdb -pg $(INCLUDES) -o $@ $<

libkv.yy.c: src/grammar.l
	$(LEX) --header-file=libkv.yy.h -f -o $@ $<


$(OUTPUT): $(OUTPUT_LIB) 
	$(CC) $(patsubst %.c,%.o,$(OUTPUT_SRC)) -o $(OUTPUT) $(LINKFLAGS)

$(OUTPUT_LIB): $(OBJECTS)
	$(RM) -f $(OUTPUT_LIB)
	$(AR) cr $(OUTPUT_LIB) $(OBJECTS_LIB)
	ranlib $(OUTPUT_LIB)

lint:
	splint *.c

clean :
	rm $(OBJECTS) $(OUTPUT) $(OUTPUT_LIB) libkv.tab.c libkv.tab.h libkv.yy.c libkv.yy.h

check-syntax: 
	gcc -o nul -S ${CHK_SOURCES} 


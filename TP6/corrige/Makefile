# file: Makefile

SHELL  = /bin/bash
CC     = gcc
CFLAGS = -std=c99 -W -Wall
LIBS   = -lm

EXEC = spamhunter
TARGET_DIR = bin
HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
MODULES = $(basename $(SOURCES))
OBJECTS = $(addsuffix .o , $(MODULES))

$(EXEC): $(OBJECTS)
	@echo === GENERATING PROGRAM $@ ===
	$(CC) $^ $(LIBS) -o $@

%.o : %.c
	@echo === COMPILING $@ ===
	$(CC) $< $(CFLAGS) -c

depend: $(HEADERS) $(SOURCES)
	@echo === COMPUTING DEPENDANCIES $@ ===
	$(CC) -MM $(SOURCES) >|  $@

install: $(EXEC)
	@echo === INSTALLING PROGRAM $(EXEC) ===
	mkdir -p $(TARGET_DIR)
	cp $(EXEC) $(TARGET_DIR)

clean::
	@echo === DELETING OBJECT FILES ===
	rm -f *.o

mrpropre: clean
	@echo === DELETING PROGRAM $(EXEC) ===
	rm -f $(EXEC)

rebuild:: mrpropre $(EXEC)

-include depend

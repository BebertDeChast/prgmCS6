# file: Makefile mono

SHELL  = /bin/bash
CC     = gcc
CFLAGS = -W -Wall
LIBS   = -lm

EXEC = main
TARGET_DIR = bin
HEADERS = $($(EXEC) *.h)
SOURCES = $($(EXEC) *.c)
MODULES = $(basename $(SOURCES))
OBJECTS = $(addsuffix .o , $(MODULES))

$(EXEC): $(OBJECTS)
	@echo === GENERATING PROGRAM $@ ===
	$(CC) $^ $(LIBS) -o $@
	make clean

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
	rm -f ./depend

mrpropre: clean
	@echo === DELETING PROGRAM $(EXEC) ===
	rm -f $(EXEC) 

rebuild:: mrpropre $(EXEC)

-include depend

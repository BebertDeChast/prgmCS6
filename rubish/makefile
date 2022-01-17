CC = gcc
CFLAGS = -std=c99 -W -Wall
LIBS = -lm

EXEC = prog
HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
MODULES = $(basename $(SOURCES))
OBJECTS = $(addsuffix .o ,$(MODULES))

$(EXEC): $(OBJECTS)
		$(CC) $^ $(LIBS) -o $@

%.o : %.c 
		$(CC) $< $(CFLAGS) -c

depend: $(HEADERS) $(SOURCES)
		$(CC) -MM $(SOURCES) >| $@

clean::
		rm -f *.o


-include depend
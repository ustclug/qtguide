# Makefile for building: hellorect
CC          = gcc
CXX         = g++
LINKER      = g++
LFLAGS      = -lm -static

OBJECTS     = rect.o hellorect.o
DSTTARGET   = hellorect
# Default rule
all: $(DSTTARGET)


$(DSTTARGET): $(OBJECTS)
	$(LINKER)  $(LFLAGS)  -o $@  $(OBJECTS)

hellorect.o: hellorect.cpp
	$(CXX) -c  -o  $@  $<  

rect.o: rect.cpp
	$(CXX) -c  -o  $@  $<  

clean:
	rm  $(OBJECTS)  hellorect.exe

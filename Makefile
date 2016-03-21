CC=clang++
CFLAGS= -std=c++11 -Wall -O2
EXE=smartgrid

.PHONY: all clean

all: $(EXE)

$(EXE): main.cpp point.o vertex.o edge.o node.o source.o resident.o wire.o
	$(CC) $(CFLAGS) -o $(EXE) main.cpp point.o vertex.o edge.o node.o source.o resident.o wire.o

point.o: point.hpp point.cpp
	$(CC) $(CFLAGS) -c point.cpp

vertex.o: vertex.hpp vertex.cpp
	$(CC) $(CFLAGS) -c vertex.cpp

edge.o: edge.hpp edge.cpp
	$(CC) $(CFLAGS) -c edge.cpp

node.o: node.hpp node.cpp
	$(CC) $(CFLAGS) -c node.cpp

source.o: source.hpp source.cpp
	$(CC) $(CFLAGS) -c source.cpp

resident.o: resident.hpp resident.cpp
	$(CC) $(CFLAGS) -c resident.cpp

wire.o: wire.hpp wire.cpp
	$(CC) $(CFLAGS) -c wire.cpp

clean:
	rm -rf $(EXE) *.o

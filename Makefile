SOURCE_PATH = ./source

default: all

all: build build/protoTerminal

build: 
	mkdir build

commands.o: ${SOURCE_PATH}/commands.cpp
	g++ -c ${SOURCE_PATH}/commands.cpp -o ${SOURCE_PATH}/commands.o

protoTerminal.o: protoTerminal.cpp
	g++ -c protoTerminal.cpp

build/protoTerminal: protoTerminal.o ${SOURCE_PATH}/commands.o
	g++ -o build/protoTerminal protoTerminal.o ${SOURCE_PATH}/commands.o

clean:
	rm -rf *.o
	rm -rf ${SOURCE_PATH}/*.o
	rm -rf build/*

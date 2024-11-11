CC = g++
CFLAGS = -std=c++17 -Wall

# Diretórios
OBJ = ./obj
BIN = ./bin
INCLUDE = ./include
SRC = ./src

target = ${BIN}/main.out

all:
	make ${OBJ}/grafo.o
	make ${OBJ}/main.o
	make ${target}
	${target}

${target}: ${OBJ}/*
	${CC} ${CFLAGS} ${OBJ}/* -o ${target}

${OBJ}/main.o: ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/main.cpp -o ${OBJ}/main.o

${OBJ}/grafo.o: ${SRC}/grafo.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/grafo.cpp -o ${OBJ}/grafo.o
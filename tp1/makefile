CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# Diretórios
OBJ = ./obj
BIN = ./bin
INCLUDE = ./include
SRC = ./src

target = ${BIN}/main.out

all:
	mkdir -p bin
	mkdir -p obj
	make ${OBJ}/grafo.o
	make ${OBJ}/estado.o
	make ${OBJ}/main.o
	make ${target}

run:
	${target} < teste1.txt
	${target} < teste2.txt
	${target} < teste3.txt

${target}: ${OBJ}/*
	${CC} ${CFLAGS} ${OBJ}/* -o ${target}

${OBJ}/main.o: ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/main.cpp -o ${OBJ}/main.o

${OBJ}/grafo.o: ${SRC}/grafo.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/grafo.cpp -o ${OBJ}/grafo.o

${OBJ}/estado.o: ${SRC}/estado.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/estado.cpp -o ${OBJ}/estado.o

clean:
	rm -r ./obj/*.o
	rm -r ./bin/*.*

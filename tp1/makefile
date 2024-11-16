CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# Diretórios
OBJ = ./obj
BIN = ./bin
INCLUDE = ./include
SRC = ./src
TEST = ./inputs

target = ${BIN}/tp1

all:
	mkdir -p bin
	mkdir -p obj
	make ${OBJ}/grafo.o
	make ${OBJ}/estado.o
	make ${OBJ}/main.o
	make ${target}
	make valgrind

run:
	$(target) < $(TEST)/testCase01.txt
	$(target) < $(TEST)/testCase02.txt
	$(target) < $(TEST)/testCase03.txt
	$(target) < $(TEST)/testCase04.txt
	$(target) < $(TEST)/testCase05.txt
	$(target) < $(TEST)/testCase06.txt
	$(target) < $(TEST)/testCase07.txt
	$(target) < $(TEST)/testCase08.txt
	valgrind ${BIN}/mentest < teste2.txt

${target}: ${OBJ}/*
	${CC} ${CFLAGS} ${OBJ}/* -o ${target}

valgrind: ${OBJ}/*
	${CC} ${CFLAGS} -g ${OBJ}/* -o ${BIN}/mentest

${OBJ}/main.o: ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/main.cpp -o ${OBJ}/main.o

${OBJ}/grafo.o: ${SRC}/grafo.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/grafo.cpp -o ${OBJ}/grafo.o

${OBJ}/estado.o: ${SRC}/estado.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/estado.cpp -o ${OBJ}/estado.o

clean:
	rm -r ./obj/*.o
	rm ./bin/*

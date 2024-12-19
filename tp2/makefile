CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# Diretórios
OBJ = ./obj
BIN = ./bin
INCLUDE = ./include
SRC = ./src
TEST = ./inputs

target = ${BIN}/tp2

all:
	mkdir -p bin
	mkdir -p obj
	make ${OBJ}/Grafo.o
	make ${OBJ}/NetworkAnalysis.o
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
other:	
	valgrind ${BIN}/mentest < $(TEST)/testCase01.txt

${target}: ${OBJ}/*
	${CC} ${CFLAGS} ${OBJ}/* -o ${target}

valgrind: ${OBJ}/*
	${CC} ${CFLAGS} -g ${OBJ}/* -o ${BIN}/mentest

${OBJ}/main.o: ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/main.cpp -o ${OBJ}/main.o

${OBJ}/Grafo.o: ${SRC}/Grafo.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/Grafo.cpp -o ${OBJ}/Grafo.o

${OBJ}/NetworkAnalysis.o: ${SRC}/NetworkAnalysis.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/NetworkAnalysis.cpp -o ${OBJ}/NetworkAnalysis.o

clean:
	rm -r ./obj/*.o
	rm ./bin/*

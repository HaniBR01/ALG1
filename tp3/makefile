CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# Diretórios
OBJ = ./obj
BIN = ./bin
INCLUDE = ./include
SRC = ./src
TEST = ./inputs

target = ./tp3

all:
	make clean
	mkdir -p bin
	mkdir -p obj
	make Grafo.o
	make Greedy.o
	make BruteForce.o
	make Dynamic.o
	make main.o
	make target
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
	$(target) < $(TEST)/testCase09.txt
	$(target) < $(TEST)/testCase10.txt
other:	
	valgrind -s ${BIN}/mentest < $(TEST)/testCase01.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase02.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase03.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase04.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase05.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase06.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase07.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase08.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase09.txt
	valgrind -s ${BIN}/mentest < $(TEST)/testCase10.txt

target: ${OBJ}/*
	${CC} ${CFLAGS} ${OBJ}/* -o ${target}

valgrind: ${OBJ}/*
	${CC} ${CFLAGS} -g ${OBJ}/* -o ${BIN}/mentest

main.o: ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/main.cpp -o ${OBJ}/main.o

Grafo.o: ${SRC}/Grafo.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/Grafo.cpp -o ${OBJ}/Grafo.o

Greedy.o: ${SRC}/Greedy.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/Greedy.cpp -o ${OBJ}/Greedy.o

Dynamic.o: ${SRC}/Dynamic.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/Dynamic.cpp -o ${OBJ}/Dynamic.o

BruteForce.o: ${SRC}/BruteForce.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/BruteForce.cpp -o ${OBJ}/BruteForce.o


clean:
	rm -r ./obj/*.o
	rm ./bin/*
	rm ./tp3

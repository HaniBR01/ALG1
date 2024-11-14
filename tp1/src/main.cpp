#include <iostream>
#include <string>
#include "grafo.hpp"
#include "estado.hpp"

using namespace std;

int main() {
    int n, m;
    cout << "Digite o número de cidades (nós): ";
    cin >> n;
    cout << "Digite o número de estradas (arestas): ";
    cin >> m;

    Estado brazil(n,m);

    brazil.printCapital();
    brazil.printCFCS();
    brazil.printBatalhoes();
    brazil.printPatrulhamento();

    return 0;
}

#include <iostream>
#include <string>
#include "grafo.hpp"
#include "estado.hpp"

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    Estado brazil(n,m);

    brazil.printCapital();
    //brazil.printCFCS();
    brazil.printBatalhoes();
    brazil.printPatrulhamento();

    return 0;
}

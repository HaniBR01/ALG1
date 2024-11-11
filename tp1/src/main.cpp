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

    cout << "capital: " << brazil.encontrarCapital() << "\n\n";
    vector<vector<string>> kosaraju = brazil.kosaraju();

    for (const auto& cfc : kosaraju) {
        cout << "Componente fortemente conectada: ";
        for (const auto& cidade : cfc) {
            cout << cidade << " ";
        }
        cout << endl;
    }

    return 0;
}

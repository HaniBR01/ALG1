#include <iostream>
#include <string>
#include "grafo.hpp"

using namespace std;

int main() {
    int n, m;
    cout << "Digite o número de cidades (nós): ";
    cin >> n;
    cout << "Digite o número de estradas (arestas): ";
    cin >> m;

    Grafo grafo;

    // Lê as arestas
    cout << "Digite as " << m << " estradas (saída, destino):" << endl;
    for (int i = 0; i < m; ++i) {
        string cidadeSaida, cidadeDestino;
        cin >> cidadeSaida >> cidadeDestino;
        grafo.addEstrada(cidadeSaida, cidadeDestino);
    }

    // Aqui você pode chamar funções como encontrar a capital, verificar ciclos, etc.
    string capital = grafo.encontrarCapital();
    if (capital.empty()) {
        cout << "Não há uma cidade central, o grafo não é conexo." << endl;
    } else {
        cout << "A cidade capital é: " << capital << endl;
    }

    return 0;
}

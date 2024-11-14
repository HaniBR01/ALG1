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

    cout << "capital: " << brazil.encontrarCapital() << endl;

    pair<int, vector<string>> kosaraju = brazil.kosaraju();
    cout << kosaraju.first << " Batalhão(s) extra em: ";
    for (const auto& cidade : kosaraju.second) {
        cout << cidade << " ";
    }
    cout << endl;

    auto patrulhamentos = brazil.realizarPatrulhamento();

    // Imprime os resultados do patrulhamento
    if (patrulhamentos.empty()) {
        std::cout << "Nenhum circuito Euleriano encontrado para patrulhamento.\n";
    } else {
        std::cout << "Circuitos de patrulhamento encontrados:\n";
        for (const auto& [batalhao, circuito] : patrulhamentos) {
            std::cout << "Batalhão: " << batalhao << "\nRota de patrulhamento: ";
            for (const auto& cidade : circuito) {
                std::cout << cidade << " -> ";
            }
            std::cout << circuito.front() << " (volta ao início)\n";  // Para completar o ciclo
            std::cout << "----------------------------------\n";
        }
    }

    return 0;
}

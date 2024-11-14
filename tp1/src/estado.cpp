#include "estado.hpp"

Estado::Estado(int n, int m) {

    centros = n;
    estradas = m;
    capital = "";
    // Lê as arestas
    cout << "Digite as " << estradas << " estradas (saída, destino):" << endl;
    for (int i = 0; i < m; ++i) {
        string cidadeSaida, cidadeDestino;
        cin >> cidadeSaida >> cidadeDestino;
        Imperio.addEstrada(cidadeSaida, cidadeDestino);
    }
}

string Estado::encontrarCapital(){
    vector<string> cidades = Imperio.getCidades();
    int distanciaMinima = centros + 1; 
    string cidadeCapital;

    for (const auto& cidade : cidades) {
        int* distanciaMaxima = Imperio.bfsDistanciaMaxima(cidade);
        if (distanciaMaxima[0] < distanciaMinima && distanciaMaxima[1] >= centros) {
            distanciaMinima = distanciaMaxima[0];
            cidadeCapital = cidade;
            delete distanciaMaxima;
        }
    }
    capital = cidadeCapital;
    return cidadeCapital;
}

bool Estado::encontrarCapital(const vector<string>& componente, const string& capital) const {
    for (const auto& cidade : componente) {
        if (cidade == capital) {
            return true;
        }
    }
    return false;
}

pair<int, vector<string>> Estado::kosaraju() {
    // Inicialize um vetor de pares para armazenar a quantidade de batalhões e seus locais
    pair<int, vector<string>> batalhoesForaDaCapital;
    
    // Aqui, vamos rodar o algoritmo de Kosaraju no grafo `Imperio` e,
    // com base no resultado, determinar quantos batalhões extras são necessários em cada local.

    // Exemplo de lógica fictícia:
    vector<vector<string>> cfcs = Imperio.kosaraju();
    for (const auto& componente : cfcs) {
        // Verifique se o local não é a capital e calcule os batalhões necessários
        if (!encontrarCapital(componente,capital)) {
            batalhoesForaDaCapital.second.push_back(componente[0]);
            batalhoesForaDaCapital.first++;
        }
    }
    return batalhoesForaDaCapital;
}

vector<pair<string, vector<string>>> Estado::realizarPatrulhamento() {
    vector<vector<string>> cfcs = Imperio.kosaraju();
    vector<pair<string, vector<string>>> patrulhamentos;

    for (const auto& cfc : cfcs) {
        if (Imperio.verificaEuleriano(cfc)) {
            vector<string> circuito = Imperio.hierholzer(cfc);
            if (!circuito.empty()) {
                patrulhamentos.emplace_back(cfc.front(), circuito);
            }
        }
    }
    return patrulhamentos;
}
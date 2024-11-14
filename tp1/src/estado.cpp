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

    encontrarCapital();
    kosaraju();
    realizarPatrulhamento();
}

void Estado::encontrarCapital(){
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
}

void Estado::printCapital(){
    cout << "capital: " << capital << endl;
}

bool Estado::encontrarCapital(const vector<string>& componente, const string& capital) const {
    for (const auto& cidade : componente) {
        if (cidade == capital) {
            return true;
        }
    }
    return false;
}

void Estado::kosaraju() {
    // Inicialize um vetor de pares para armazenar a quantidade de batalhões e seus locais
    pair<int, vector<string>> batalhoesForaDaCapital;
    
    // Aqui, vamos rodar o algoritmo de Kosaraju no grafo `Imperio` e,
    // com base no resultado, determinar quantos batalhões extras são necessários em cada local.

    // Exemplo de lógica fictícia:
    cfcs = Imperio.kosaraju();
    for (const auto& componente : cfcs) {
        // Verifique se o local não é a capital e calcule os batalhões necessários
        if (!encontrarCapital(componente,capital)) {
            batalhoesForaDaCapital.second.push_back(componente[0]);
            batalhoesForaDaCapital.first++;
        }
    }
    batalhoes = batalhoesForaDaCapital;
}

void Estado::printBatalhoes() {
    cout << "Batalhões necessários fora da capital:" << endl;
    
    if (batalhoes.first == 0) {
        cout << "Nenhum batalhão adicional é necessário fora da capital." << endl;
        return;
    }

    cout << "Número de batalhões fora da capital: " << batalhoes.first << endl;
    cout << "Centros urbanos com batalhões adicionais:" << endl;
    
    for (const auto& centro : batalhoes.second) {
        cout << "- " << centro << endl;
    }
}

void Estado::printCFCS() {
    for (size_t i = 0; i < cfcs.size(); ++i) {
        cout << "CFC " << i + 1 << ": ";
        for (const auto& node : cfcs[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
}

void Estado::realizarPatrulhamento() {
    if(cfcs.empty()){
        cfcs = Imperio.kosaraju();
    }
    vector<pair<string, vector<string>>> patrulhas;

    for (const auto& cfc : cfcs) {
        if (Imperio.verificaEuleriano(cfc)) {
            vector<string> circuito = Imperio.hierholzer(cfc);
            if (!circuito.empty()) {
                patrulhas.emplace_back(cfc.front(), circuito);
            }
        }
    }
    patrulhamentos = patrulhas;
}

void Estado::printPatrulhamento() {
    cout << "Circuitos de patrulhamento encontrados:" << endl;
    for (const auto& patrulha : patrulhamentos) {
        const string& batalhao = patrulha.first;
        const vector<string>& rota = patrulha.second;
        
        cout << "Batalhão: " << batalhao << endl;
        cout << "Rota de patrulhamento (inverso): ";
        
        // Printando a rota na ordem inversa
        for (int i = rota.size() - 1; i > 0; --i) {
            cout << rota[i] << " ";
        }
        cout << endl << "----------------------------------" << endl;
    }
}

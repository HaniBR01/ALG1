#include "estado.hpp"

Estado::Estado(int n, int m) {

    centros = n;
    estradas = m;
    capital = "";
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

void Estado::kosaraju() {
    // Inicialize um vetor de pares para armazenar a quantidade de batalhões e seus locais
    pair<int, vector<string>> batalhoesForaDaCapital;
    
    // Aqui, vamos rodar o algoritmo de Kosaraju no grafo `Imperio` e,
    // com base no resultado, determinar quantos batalhões extras são necessários em cada local.

    // Exemplo de lógica fictícia:
    cfcs = Imperio.kosaraju();
    for (const auto& componente : cfcs) {
        // Verifique se o local não é a capital e calcule os batalhões necessários
        if (!Imperio.buscaCidade(componente, capital)) {
            batalhoesForaDaCapital.second.push_back(componente[0]);
            batalhoesForaDaCapital.first++;
        }
    }
    batalhoes = batalhoesForaDaCapital;
}

void Estado::realizarPatrulhamento() {
    if (cfcs.empty()) {
        cfcs = Imperio.kosaraju();
    }
    vector<pair<string, vector<string>>> patrulhas;

    for (const auto& cfc : cfcs) {
        if (cfc.size() > 1) {
            if (Imperio.verificaEuleriano(cfc)) {
                // Se a CFC é euleriana, usa o algoritmo de Hierholzer normalmente
                vector<string> circuito = Imperio.hierholzer(cfc);
                if (!circuito.empty()) {
                    patrulhas.emplace_back(cfc.front(), circuito);
                }
            } else {
                // 1. Identificar vértices desbalanceados
                vector<string> excessosEntrada, excessosSaida;
                Imperio.identificarExcessos(cfc, excessosEntrada, excessosSaida);

                // 2. Balancear o grafo: encontrar caminhos entre excessos de saída e entrada
                vector<pair<string, string>> caminhosParaDuplicar;
                for (const auto& saida : excessosSaida) {
                    for (const auto& entrada : excessosEntrada) {
                        if (Imperio.hasEstrada(saida, entrada)) {
                            caminhosParaDuplicar.emplace_back(saida, entrada);
                            break;  // Saia após encontrar um caminho
                        }
                    }
                }

                // 3. Duplicar as arestas dos caminhos encontrados
                for (const auto& caminho : caminhosParaDuplicar) {
                    Imperio.addEstrada(caminho.first, caminho.second);
                }

                // 4. Executar o Kosaraju e realizar o patrulhamento após o balanceamento
                vector<string> circuito = Imperio.hierholzer(cfc);
                if (!circuito.empty()) {
                    patrulhas.emplace_back(cfc.front(), circuito);
                }
            }
        }
    }
    patrulhamentos = patrulhas;
}

void Estado::printCapital(){
    cout << capital << endl;
}

void Estado::printBatalhoes() {

    cout << batalhoes.first << endl;
    
    for (const auto& centro : batalhoes.second) {
        cout << centro << " " << endl;
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

void Estado::printPatrulhamento() {
    cout << patrulhamentos.size() << endl;
    for (const auto& patrulha : patrulhamentos) {
        const vector<string>& rota = patrulha.second;
    for (size_t i = rota.size() - 1; i > 0; --i) {
            cout << rota[i] << " ";
        }
        cout << endl;
    }
}

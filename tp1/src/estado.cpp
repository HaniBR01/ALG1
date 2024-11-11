#include "estado.hpp"

Estado::Estado(int n, int m) {

    centros = n;
    estradas = m;
    // Lê as arestas
    cout << "Digite as " << estradas << " estradas (saída, destino):" << endl;
    for (int i = 0; i < m; ++i) {
        string cidadeSaida, cidadeDestino;
        cin >> cidadeSaida >> cidadeDestino;
        Imperio.addEstrada(cidadeSaida, cidadeDestino);
    }
}

string Estado::encontrarCapital() const {
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

    return cidadeCapital;
}
vector<vector<string>> Estado::kosaraju(){
    return Imperio.kosaraju();
}
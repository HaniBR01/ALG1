#include "Grafo.hpp"

Grafo::Grafo(int vertices, int arestas){
    int custo;
    int indice = 0;
    std::string origem, destino; 

    matriz = std::vector<std::vector<int>>(vertices, std::vector<int>(vertices, 0));  

    for(int i = 0; i < arestas; i++){
        std::cin >> origem >> destino >> custo;
		
		if(map.find(origem) == map.end()){
    		cidades.push_back(origem);
			map.insert({origem,indice++});
        }
        if(map.find(destino) == map.end()){
    		cidades.push_back(destino);
			map.insert({destino,indice++});
        }
        addAresta(origem, destino, custo);
    }
    if(int(map.size()) != vertices-1)
        std::cout << "erro";
}

void Grafo::addVertice(std::string cidade, int indice){
    cidades.push_back(cidade);
	indice = (indice+1) * 2 -2;
}

void Grafo::addAresta(std::string origem, std::string destino, int custo){
    int i = map[origem];
	int j = map[destino];
	
    matriz[i][j] = custo;
    matriz[j][i] = custo;
}

void Grafo::print(std::pair<int, std::vector<int>> vec){
    std::cout << "Custo: " << vec.first << std::endl;
    int n = int(vec.second.size());
    for(int i = 0; i < n; i++){
        std::string c = cidades[vec.second[i]];
        if(i == n-1)
            std::cout << c;
        else
            std::cout << c << " ";
    }
}
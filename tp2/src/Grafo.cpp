#include "Grafo.hpp"

// MergeSort para ordenar o vetor de tuplas de conexões críticas
void merge(std::vector<std::tuple<int, int, int>>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<std::tuple<int, int, int>> leftVec(n1), rightVec(n2);
    for (int i = 0; i < n1; ++i) {
        leftVec[i] = vec[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        rightVec[j] = vec[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (std::get<2>(leftVec[i]) >= std::get<2>(rightVec[j])) {
            vec[k] = leftVec[i];
            ++i;
        } else {
            vec[k] = rightVec[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        vec[k] = leftVec[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        vec[k] = rightVec[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<std::tuple<int, int, int>>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

Grafo::Grafo(int numVertices, int arestas){
    //Inicializando o Grafo
    fonte = std::numeric_limits<int>::max();
    dreno = std::numeric_limits<int>::min();
    energiaExigida = 0;
    energiaFornecida = 0;

    addVertice(fonte);
    addVertice(dreno);

    int id, consumo, destino, capacidade; 
    for(int i=0; i<numVertices;i++){
        std::cin >> id >> consumo;
        addVertice(id);
        energiaExigida += consumo;
        if(consumo == 0){
            addAresta(fonte,id,fonte);
        }else{
            addAresta(id,dreno,consumo);
        }
    }
    for(int i=0;i<arestas;i++){
        std::cin >> id >> destino >> capacidade;
        addAresta(id, destino, capacidade);
    }

    fordFulkerson();
    encontrarConexoesCriticas();
}

void Grafo::addVertice(int id){
    vertices.insert({id,Vertice()});
}
void Grafo::addAresta(int id, int destino, int capacidade){
    vertices[id].addAresta(destino,capacidade);
    vertices[destino].addAresta(id,0);
}

bool Grafo::bfsFordFulkerson(std::map<int, int>& parent) {
    std::map<int, bool> visited;
    for (const auto& v : vertices) {
        visited[v.first] = false;
    }
    std::queue<int> q;
    q.push(fonte);
    visited[fonte] = true;
    parent[fonte] = -1;
    //int i = 0;
    //std::cout << "start bfs" << std::endl;
    while (!q.empty()) {
        //std::cout << "testes bfs " << i++ << std::endl;
        int current = q.front();
        q.pop();
        for (const auto& aresta : vertices[current].adjList) {
            int destino = aresta.first;
            int capacidade_residual = aresta.second.capacidade - aresta.second.fluxo;
            if (!visited[destino] && capacidade_residual > 0) {
                parent[destino] = current;
                visited[destino] = true;
                if (destino == dreno) return true;
                q.push(destino);
            }
        }
    }
    return false;
}

void Grafo::fordFulkerson() {
    std::map<int, int> parent;
    int energiaAtendida = 0;
    //int i = 0;
    while (bfsFordFulkerson(parent)) {
        //std::cout << "testes " << i++ << std::endl;
        int fluxo_caminho = std::numeric_limits<int>::max();
        for (int v = dreno; v != fonte; v = parent[v]) {
            int u = parent[v];
            int residual = vertices[u].adjList[v].capacidade - vertices[u].adjList[v].fluxo;
            fluxo_caminho = std::min(fluxo_caminho, residual);
        }
        for (int v = dreno; v != fonte; v = parent[v]) {
            int u = parent[v];
            vertices[u].adjList[v].fluxo += fluxo_caminho;
            vertices[v].adjList[u].fluxo -= fluxo_caminho;
        }
        energiaAtendida += fluxo_caminho;
    }
    //std::cout << "end ford fulkerson" << std::endl;
}

int Grafo::energiaPerdida(){
    for(const auto& aresta : vertices[fonte].adjList){
        int gerador = aresta.first;
        for(const auto& aresta : vertices[gerador].adjList){
            energiaFornecida += aresta.second.capacidade;
        }
    }
    return energiaFornecida - energiaAtendida;
}

int Grafo::energiaNaoAtendida(){
    return energiaExigida - energiaAtendida;
}

void Grafo::encontrarConexoesCriticas() {
    for (const auto& [origem, vertice] : vertices) {
        for (const auto& aresta : vertice.adjList) {
            /*"""std::cout << "origem: " << origem << " destino: " << aresta.first
                        << " capacidade: " << aresta.second.capacidade
                        << " fluxo: " << aresta.second.fluxo << std::endl;"""*/
            if (aresta.second.fluxo == aresta.second.capacidade && aresta.first != dreno && aresta.second.capacidade != 0) {
                conexoesCriticas.emplace_back(origem, aresta.first, aresta.second.capacidade);
            }
        }
    }
    mergeSort(conexoesCriticas,0,static_cast<int>(conexoesCriticas.size())-1);
}

void Grafo::out(){
    int energiaNA = energiaNaoAtendida();
    int energiaP = energiaPerdida();

    std::cout << energiaAtendida << std::endl;
    std::cout << energiaNA << std::endl;
    std::cout << energiaP << std::endl;
    std::cout << conexoesCriticas.size() << std::endl;
    for (const auto& [origem, destino, capacidade] : conexoesCriticas) {
        std::cout << origem << " " << destino << " " << capacidade << std::endl;
    }
}
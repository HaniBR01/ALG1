#include "Graph.hpp"
#include <queue>
#include <limits>

Grafo::Grafo(int numVertices, int arestas) : vertices(vertices) {
    
    numVertices = numVertices;
    int id, consumo, destino, capacidade;
    int superFonte = std::numeric_limits<int>::max();
    int superDreno = -superFonte;
    addVertice(superFonte);
    addVertice(superDreno);

    for(int i=0; i<numVertices;i++){
        std::cin >> id >> consumo;
        addVertice(id,consumo);
        if(consumo == 0){
            addAresta(superFonte,id,superFonte);
        }else{
            addAresta(id,superDreno,consumo);
        }
    }
    for(int i=0;i<arestas;i++){
        std::cin >> id >> destino >> capacidade;
        addAresta(id, destino, capacidade);
    }
}

void Grafo::addVertice(int id, int consumo = 0){
    vertices.insert({id,Vertice(id,consumo)});
}
void Grafo::addAresta(int id, int destino, int capacidade){
    vertices.find(id)->second.addAresta(destino,capacidade);
    vertices.find(destino)->second.addAresta(id,0);
}

void Grafo::bfs(int start) {
    if (vertices.find(start) == vertices.end()) {
        std::cout << "Vértice inicial não encontrado.\n";
        return;
    }

    std::unordered_map<int, bool> visited;
    std::queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        std::cout << "Visitando vértice " << current << "\n";

        for (const auto& aresta : vertices[current].adjList) {
            int destino = aresta.destino;
            if (!visited[destino]) {
                q.push(destino);
                visited[destino] = true;
            }
        }
    }
}

int Grafo::getMaxFlow(int source, int sink) {
    int maxFlow = 0;
    std::vector<int> parent(vertices);

    while (bfs(parent, source, sink)) {
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            for (auto& Aresta : adjList[parent[v]]) {
                if (Aresta.to == v && Aresta.capacity > Aresta.flow) {
                    pathFlow = std::min(pathFlow, Aresta.capacity - Aresta.flow);
                }
            }
        }

        for (int v = sink; v != source; v = parent[v]) {
            for (auto& Aresta : adjList[parent[v]]) {
                if (Aresta.to == v) {
                    Aresta.flow += pathFlow;
                }
            }
            for (auto& Aresta : adjList[v]) {
                if (Aresta.to == parent[v]) {
                    Aresta.flow -= pathFlow;
                }
            }
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

std::map<int, int> Grafo::getConsumerDemands() {
    std::map<int, int> demands;
    for (int i = 0; i < vertices; ++i) {
        for (const auto& Aresta : adjList[i]) {
            if (Aresta.capacity > 0 && Aresta.flow == 0) {
                demands[i] += Aresta.capacity;
            }
        }
    }
    return demands;
}

std::map<int, int> Grafo::getGeneratorFlows() {
    std::map<int, int> flows;
    for (int i = 0; i < vertices; ++i) {
        for (const auto& Aresta : adjList[i]) {
            if (Aresta.capacity > 0 && Aresta.flow > 0) {
                flows[i] += Aresta.flow;
            }
        }
    }
    return flows;
}

const std::vector<std::vector<Grafo::Aresta>>& Grafo::getAdjList() const {
    return adjList;
}
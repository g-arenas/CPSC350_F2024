#include "WGraph.h"

WGraph::WGraph(unsigned int sz) : size(sz) {
    adjMatrix = new double*[size];
    for (unsigned int i = 0; i < size; ++i) {
        adjMatrix[i] = new double[size];
        for (unsigned int j = 0; j < size; ++j) {
            adjMatrix[i][j] = std::numeric_limits<double>::max();
        }
    }
}

WGraph::~WGraph() {
    for (unsigned int i = 0; i < size; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

void WGraph::addEdge(VertexID i, VertexID j, double w) {
    if (i < size && j < size && w > 0) {
        adjMatrix[i][j] = w;
        adjMatrix[j][i] = w; // Symmetric for undirected graph
        edges.push_back(Edge(i, j, w));
    }
}

int WGraph::findSet(int i, std::vector<int>& parent) {
    if (i == parent[i]) {
        return i;
    }
    return parent[i] = findSet(parent[i], parent);
}

void WGraph::unionSets(int a, int b, std::vector<int>& parent, std::vector<int>& rank) {
    a = findSet(a, parent);
    b = findSet(b, parent);

    if (a != b) {
        if (rank[a] < rank[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            rank[a]++;
        }
    }
}

void WGraph::computeMST() {
    std::sort(edges.begin(), edges.end());
    std::vector<int> parent(size), rank(size, 0);
    std::vector<std::vector<double> > mstMatrix(size, std::vector<double>(size, 0));
    double totalWeight = 0;

    for (unsigned int i = 0; i < size; ++i) {
        parent[i] = i;
    }

    for (const auto& edge : edges) {
        if (findSet(edge.u, parent) != findSet(edge.v, parent)) {
            totalWeight += edge.weight;
            unionSets(edge.u, edge.v, parent, rank);
            mstMatrix[edge.u][edge.v] = edge.weight;
            mstMatrix[edge.v][edge.u] = edge.weight;
        }
    }

    std::cout << "The MST Cost is: " << totalWeight << "\n";
    for (const auto& row : mstMatrix) {
        for (const auto& weight : row) {
            std::cout << weight << " ";
        }
        std::cout << "\n";
    }
}

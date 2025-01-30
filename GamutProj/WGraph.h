#ifndef WGRAPH_H
#define WGRAPH_H

#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

typedef unsigned int VertexID;

class WGraph {
public:
    WGraph(unsigned int sz);
    ~WGraph();
    void addEdge(VertexID i, VertexID j, double w);
    void computeMST();

private:
    struct Edge {
        VertexID u, v;
        double weight;

        Edge(VertexID u, VertexID v, double weight) : u(u), v(v), weight(weight) {}

        bool operator<(const Edge& e) const {
            return weight < e.weight;
        }
    };

    std::vector<Edge> edges;
    unsigned int size;
    double** adjMatrix;

    int findSet(int i, std::vector<int>& parent);
    void unionSets(int a, int b, std::vector<int>& parent, std::vector<int>& rank);
};

#endif

#include <iostream>
#include <fstream>
#include <string>
#include "WGraph.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << argv[1] << "\n";
        return 1;
    }

    unsigned int N;
    if (!(file >> N)) {
        std::cerr << "Unable to read number of nodes\n";
        return 1;
    }

    WGraph graph(N);

    for (unsigned int i = 0; i < N; ++i) {
        for (unsigned int j = 0; j < N; ++j) {
            double weight;
            if (!(file >> weight)) {
                std::cerr << "Unable to read edge weight at (" << i << ", " << j << ")\n";
                return 1;
            }

            if (weight != 0) {
                graph.addEdge(i, j, weight);
            }
        }
    }

    std::string endMarker;
    file >> endMarker;
    if (endMarker != "END") {
        std::cerr << "File format error: Missing END marker\n";
        return 1;
    }

    file.close();

    graph.computeMST();

    return 0;
}

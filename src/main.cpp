#include <iostream>
#include <vector>

int main() {

    const int numNodes = 6;

    std::vector<std::vector<int>> adjacencyMatrix(numNodes, std::vector<int>(numNodes, 0));

    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[0][3] = 1;

    adjacencyMatrix[1][3] = 1;
    adjacencyMatrix[1][4] = 1;

    adjacencyMatrix[2][3] = 1;
    adjacencyMatrix[2][5] = 1;

    adjacencyMatrix[3][4] = 1;
    adjacencyMatrix[3][5] = 1;

    adjacencyMatrix[4][5] = 1;

    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
        }
    }

    std::cout << "Adjacency matrix of the undirected graph:" << std::endl;
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
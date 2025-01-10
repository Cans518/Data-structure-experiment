#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>

struct Edge {
    char vertex1, vertex2;
    Edge* next; // Pointer to the next edge in the list

    Edge(char v1, char v2) : vertex1(v1), vertex2(v2), next(nullptr) {}
};

struct Vertex {
    char id;
    Edge* edgeList; // Pointer to the first edge of this vertex

    Vertex(char id) : id(id), edgeList(nullptr) {}
};

class Graph {
private:
    std::vector<Vertex*> vertices;
    std::map<char, Vertex*> vertexMap; // For quick vertex lookup

    void addEdgeHelper(char v1, char v2) {
        if (vertexMap.find(v1) == vertexMap.end() || vertexMap.find(v2) == vertexMap.end()) {
            std::cerr << "Error: One or both vertices not found." << std::endl;
            return;
        }

        // Check for duplicate edges
        Edge* current = vertexMap[v1]->edgeList;
        while (current) {
            if ((current->vertex1 == v1 && current->vertex2 == v2) ||
                (current->vertex1 == v2 && current->vertex2 == v1)) {
                return; // Edge already exists
            }
            current = current->next;
        }

        // Add edge to vertex1's list
        Edge* newEdge1 = new Edge(v1, v2);
        newEdge1->next = vertexMap[v1]->edgeList;
        vertexMap[v1]->edgeList = newEdge1;

        // Add edge to vertex2's list
        Edge* newEdge2 = new Edge(v2, v1);
        newEdge2->next = vertexMap[v2]->edgeList;
        vertexMap[v2]->edgeList = newEdge2;
    }

    void clearEdges(Vertex* vertex) {
        Edge* edge = vertex->edgeList;
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            delete temp;
        }
    }

public:
    Graph(const std::vector<char>& nodeNames) {
        for (char name : nodeNames) {
            Vertex* newVertex = new Vertex(name);
            vertices.push_back(newVertex);
            vertexMap[name] = newVertex;
        }
    }

    ~Graph() {
        for (auto vertex : vertices) {
            clearEdges(vertex);
            delete vertex;
        }
    }

    void addEdge(char v1, char v2) {
        if (v1 == v2) {
            std::cerr << "Error: Cannot add self-loop." << std::endl;
            return;
        }
        addEdgeHelper(v1, v2);
    }

    void printGraph() const {
        for (auto vertex : vertices) {
            std::cout << "Vertex " << vertex->id << " is connected to: ";
            std::set<char> neighbors; // To avoid duplicate printing
            Edge* edge = vertex->edgeList;
            while (edge) {
                neighbors.insert(edge->vertex2);
                edge = edge->next;
            }
            for (char neighbor : neighbors) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

void DFS(char start) const {
    if (vertexMap.find(start) == vertexMap.end()) {
        std::cerr << "Error: Start vertex not found." << std::endl;
        return;
    }

    std::map<char, bool> visited;
    std::stack<char> stack;

    stack.push(start);

    std::cout << "DFS traversal starting from " << start << ": ";
    while (!stack.empty()) {
        char current = stack.top();
        stack.pop();

        if (!visited[current]) {
            std::cout << current << " ";
            visited[current] = true;
        }

        Edge* edge = vertexMap.at(current)->edgeList;
        while (edge) {
            char adjacentVertex = edge->vertex2;
            if (!visited[adjacentVertex]) {
                stack.push(adjacentVertex);
            }
            edge = edge->next;
        }
    }
    std::cout << std::endl;
}


    void BFS(char start) const {
        if (vertexMap.find(start) == vertexMap.end()) {
            std::cerr << "Error: Start vertex not found." << std::endl;
            return;
        }

        std::map<char, bool> visited;
        std::queue<char> queue;

        queue.push(start);
        visited[start] = true;

        std::cout << "BFS traversal starting from " << start << ": ";
        while (!queue.empty()) {
            char current = queue.front();
            queue.pop();
            std::cout << current << " ";

            Edge* edge = vertexMap.at(current)->edgeList;
            while (edge) {
                char adjacentVertex = edge->vertex2;
                if (!visited[adjacentVertex]) {
                    visited[adjacentVertex] = true;
                    queue.push(adjacentVertex);
                }
                edge = edge->next;
            }
        }
        std::cout << std::endl;
    }
};

#endif // GRAPH_HPP

# 实验07

## 实验内容
### 第一题：
画出下图所示的无向图的邻接多重表，使得其中每个无向边结点中第一个顶点序号小于第二个顶点序号，且每个顶点的各邻接边的链接顺序，为它所邻接到的顶点序号由小到大的顺序。列出深度优先和广度优先搜索遍历该图所得顶点序列和边的序列。
![alt text](image1.png)

### 第二题：
请对下图所示的有向图，请给出该图的：
（1）每一个顶点的入度和出度；
（2）写出它的邻接矩阵
（3）邻接表
（4）逆邻接表
（5）十字链表。

![alt text](image2.png)

### 第三题：
请对下图所示的无向带权图：
（1）写出它的邻接矩阵；
（2）写出它的邻接表。
（3）写出它的邻接多重表。

![alt text](image3.png)


## 实现
> 实现的文件结构如下： `include`目录下是类定义的.h文件，`lib`目录下是类实现的.cpp文件，`src`目录下是主函数，`test`目录下是测试文件。
> 因为使用模板类所以使用.hpp保证模板类的实现的可见性
> 本次三个小题在`test`文件夹下有单独的测试文件，在`main.cpp`中有三者统一的测试文件


## 实验现象

### 题目一

实现代码如下：
```cpp
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
```
测试用例:
```cpp
#include "Graph.hpp"

int main() {
    // 定义节点名称
    std::vector<char> nodeNames = {'A', 'B', 'C', 'D', 'E', 'F'};

    // 创建图
    Graph g(nodeNames);

    // 添加边
    g.addEdge('A', 'B'); // A-B
    g.addEdge('A', 'D'); // A-D
    g.addEdge('B', 'D'); // B-D
    g.addEdge('B', 'E'); // B-E
    g.addEdge('C', 'D'); // C-D
    g.addEdge('C', 'F'); // C-F
    g.addEdge('D', 'E'); // D-E
    g.addEdge('D', 'F'); // D-F
    g.addEdge('E', 'F'); // E-F

    // 输出图的邻接多重表
    g.printGraph();

    // 深度优先遍历
    g.DFS('A');

    // 广度优先遍历
    g.BFS('A');

    return 0;
}
```
实验输出：
![alt text](image.png)

```txt
Vertex A is connected to: B D 
Vertex B is connected to: A D E
Vertex C is connected to: D F
Vertex D is connected to: A B C E F
Vertex E is connected to: B D F
Vertex F is connected to: C D E
DFS traversal starting from A: A B D C F E
BFS traversal starting from A: A D B F E C
```

### 题目二

#### 2.1

```txt 
A: 出度2；入度2
B: 出度2；入度0
C: 出度1；入度2
D: 出度0；入度3
E: 出度1；入度2
F: 出度3；入度0
```

#### 2.2

| |A|B|C|D|E|F|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|**A**|0|0|1|1|0|0|
|**B**|1|0|0|0|1|0|
|**C**|0|0|0|1|0|0|
|**D**|0|0|0|0|0|0|
|**E**|1|0|0|0|0|0|
|**F**|0|0|1|1|1|0|

#### 2.3
- 邻接表

```txt
A: C, D
B: A, E
C: D
D:
E: A
F: C, D, E
```

2.4
-逆邻接表

```txt
A: B, E
B:
C: A, F
D: A, C, F
E: B, F
F:
```

#### 2.5
- 十字链表

```txt
A:
出边: (A, C), (A, D)
入边: (B, A), (E, A)
B:
出边: (B, A), (B, E)
入边:
C:
出边: (C, D)
入边: (A, C), (F, C)
D:
出边:
入边: (A, D), (C, D), (F, D)
E:
出边: (E, A)
入边: (B, E), (F, E)
F:
出边: (F, C), (F, D), (F, E)
入边:
```

### 题目三

#### 3.1
- 相邻矩阵

|   | A  | B  | C  | D  | E  | F  |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **A** | 0  | 10 | 4  | 8  | 0  | 0  |
| **B** | 10 | 0  | 0  | 2  | 8  | 0  |
| **C** | 4  | 0  | 0  | 10 | 0  | 10 |
| **D** | 8  | 2  | 10 | 0  | 8  | 5  |
| **E** | 0  | 8  | 0  | 8  | 0  | 3  |
| **F** | 0  | 0  | 10 | 5  | 3  | 0  |


#### 3.2
- 邻接表

```txt
A → (B, 10) → (C, 4) → (D, 8)

B → (A, 10) → (D, 2) → (E, 8)

C → (A, 4) → (D, 10) → (F, 10)

D → (A, 8) → (B, 2) → (C, 10) → (E, 8) → (F, 5)

E → (B, 8) → (D, 8) → (F, 3)

F → (C, 10) → (D, 5) → (E, 3)
```

#### 3.3
- 邻接多重表

```txt
顶点表：
    A: firstEdge → (A, B, 10)
    B: firstEdge → (B, A, 10)
    C: firstEdge → (C, A, 4)
    D: firstEdge → (D, A, 8)
    E: firstEdge → (E, B, 8)
    F: firstEdge → (F, C, 10)

边表
    (A, B, 10):
        ilink → (A, C, 4)
        jlink → (B, D, 2)

    (A, C, 4):
        ilink → (A, D, 8)
        jlink → (C, D, 10)

    (A, D, 8):
        ilink → nullptr
        jlink → (D, B, 2)

    (B, D, 2):
        ilink → (B, E, 8)
        jlink → (D, C, 10)

    (B, E, 8):
        ilink → nullptr
        jlink → (E, D, 8)

    (C, D, 10):
        ilink → (C, F, 10)
        jlink → (D, E, 8)

    (C, F, 10):
        ilink → nullptr
        jlink → (F, D, 5)

    (D, E, 8):
        ilink → (D, F, 5)
        jlink → (E, F, 3)

    (D, F, 5):
        ilink → nullptr
        jlink → (F, E, 3)

    (E, F, 3):
        ilink → nullptr
        jlink → nullptr
```
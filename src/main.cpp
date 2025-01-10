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
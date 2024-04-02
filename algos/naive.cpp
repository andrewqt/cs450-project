#include <chrono>
#include <vector>
#include <iostream>

#include "Timer.h"

struct BinaryLifting {

    BinaryLifting(std::vector<std::vector<int>>& graph_, int root = 0) {
        { // Initialization
            Timer timer("Init");
            graph = graph_;
            N = graph.size();
            D = 32 - __builtin_clz(N);
            parent.resize(N, -1);
            table.resize(D, std::vector<int>(N));
        }       

        { // DFS
            Timer timer("DFS");
            dfs(root);
        }

        { // Table Building
            Timer timer("Table Building");
            for (int n = 0; n < N; n++) {
                table[0][n] = parent[n];
            }
            for (int d = 1; d < D; d++) {
                for (int n = 0; n < N; n++) {
                    if (table[d - 1][n] == -1) {
                        table[d][n] = -1;
                    }
                    else {
                        table[d][n] = table[d - 1][table[d - 1][n]];
                    }
                }
            }
        }
    }


    void dfs(int n) {
        for (int e : graph[n]) {
            if (e != parent[n]) {
                parent[e] = n;
                dfs(e);
            }
        }
    }


    int query(int n, int k) {
        int ancestor = n;
        for (int d = 0; d < D; d++) {
            if (k >> d & 1) {
                ancestor = table[d][ancestor];
            }
        }
        return ancestor;
    }


    int D;
    int N;
    std::vector<int> parent;
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> table;
};

int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> graph(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int Q;
    std::cin >> Q;
    std::vector<int> nodeQuery(Q);
    std::vector<int> kQuery(Q);
    for (int i = 0; i < Q; i++) {
        std::cin >> nodeQuery[i] >> kQuery[i];
    }
    std::cout << "done reading input" << std::endl;

    Timer timer("Total Algo");
    Timer preProcTimer("PreProcessing");
    BinaryLifting algo = BinaryLifting(graph);
    preProcTimer.stop();

    Timer queryTimer("Query");
    for (int i = 0; i < Q; i++) {
        algo.query(nodeQuery[i], kQuery[i]);
    }
    queryTimer.stop();
}

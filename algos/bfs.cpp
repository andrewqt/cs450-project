#include <chrono>
#include <vector>
#include <iostream>

#include "Timer.h"

struct BinaryLifting {

    BinaryLifting(std::vector<std::vector<int>>& graph_, int root = 0) {
        { // Initialization
            Timer timer("Init");
            std::swap(graph, graph_); 
            N = graph.size();
            D = 32 - __builtin_clz(N);
            parent.resize(N, -1);
            table.resize(D * N, -1);
            bfsQueue.resize(N);
        }

        { // BFS
            Timer timer("BFS");
            bfs(root);
        }

        { // Table Building
            Timer timer("Table Building");
            for (int n = 0; n < N; n++) {
                table[n] = parent[n];
            }
            for (int d = 1; d < D; d++) {
                for (int n = 0; n < N; n++) {
                    if (table[(d - 1) * N + n] != -1) {
                        table[d * N + n] = table[(d - 1) * N + table[(d - 1) * N + n]];
                    }
                }
            }    
        }
    }


    void bfs(int root) {
        int l = 0, r = 0;
        bfsQueue[0] = root;
        while (l <= r) {
            int n = bfsQueue[l++];
            for (int e : graph[n]) {
                if (e != parent[n]) {
                    parent[e] = n;
                    bfsQueue[++r] = e;
                }
            }
        }
    }


    int query(int n, int k) {
        int ancestor = n;
        while (k != 0) {
            int d = 31 - __builtin_clz(k);
            ancestor = table[d * N + ancestor];
            k ^= (1 << d);
        }
        return ancestor;
    }


    int D;
    int N;
    std::vector<int> dep;
    std::vector<int> parent;
    std::vector<int> table;
    std::vector<int> bfsQueue;
    std::vector<std::vector<int>> graph;
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

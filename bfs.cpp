#include <chrono>
#include <vector>
#include <iostream>

struct BinaryLifting {

    BinaryLifting(std::vector<std::vector<int>>& graph_, int root = 0) {
        graph = graph_;
        N = graph.size();
        D = 31 - __builtin_clz(N);
        parent.resize(N, -1);
        table.resize(D * N, -1);
        bfsQueue.resize(N);
        bfs(root);

        for (int n = 0; n < N; n++) {
            table[n] = parent[n];
        }
        auto start = std::chrono::high_resolution_clock::now();
        for (int d = 1; d < D; d++) {
            for (int n = 0; n < N; n++) {
                if (table[(d - 1) * N + n] != -1) {
                    table[d * N + n] = table[(d - 1) * N + table[(d - 1) * N + n]];
                }
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Table Building Elapsed Time: " << elapsed.count() << " ms" << std::endl;        
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
        for (int d = 0; d < D; d++) {
            if (k >> d & 1) {
                ancestor = table[d * N + ancestor];
            }
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
    std::cout << "done reading input" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    
    BinaryLifting algo = BinaryLifting(graph);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;    
}

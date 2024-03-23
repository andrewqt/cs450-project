#include <chrono>
#include <vector>
#include <iostream>

struct BinaryLifting {

    BinaryLifting(std::vector<std::vector<int>>& graph_, int root = 0) {
        graph = graph_;
        N = graph.size();
        D = 31 - __builtin_clz(N);
        C = 0;
        parent.resize(N, -1);
        hldId.resize(N, -1);
        size.resize(N);
        heavyChild.resize(N, -1);
        hldOrder.resize(N, -1);
        dfs1(root);
        dfs2(root);
        table.resize(D, std::vector<int>(N));
        auto start = std::chrono::high_resolution_clock::now();
        for (int n = 0; n < N; n++) {
            table[0][n] = parent[hldOrder[n]];
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
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Table Building Elapsed Time: " << elapsed.count() << " ms" << std::endl;             
    }


    void dfs1(int n) {
        size[n] = 1;
        for (int e : graph[n]) {
            if (e != parent[n]) {
                parent[e] = n;
                dfs1(e);
                size[n] += size[e];
                if (heavyChild[n] == -1 || size[e] > size[heavyChild[n]]) {
                    heavyChild[n] = e;
                }
            }
        }
    }

    
    void dfs2(int n) {
        hldOrder[C] = n;
        hldId[n] = ++C;
        if (heavyChild[n] != -1) {
            dfs2(heavyChild[n]);
        }
        for (int e : graph[n]) {
            if (e != parent[n] && e != heavyChild[n]) {
                dfs2(e);
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
    int C;
    std::vector<int> parent;
    std::vector<int> hldId;
    std::vector<int> hldOrder;
    std::vector<int> heavyChild;
    std::vector<int> size;
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
    std::cout << "done reading input" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    
    BinaryLifting algo = BinaryLifting(graph);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;    
}
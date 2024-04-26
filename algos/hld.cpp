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
            C = 0;
            parent.resize(N, -1);
            hldId.resize(N, -1);
            size.resize(N);
            heavyChild.resize(N, -1);
            hldOrder.resize(N, -1);
            table.resize(D * N, -1);
            stk.resize(N);
            dfsPtr.resize(N);
            doneHeavyChild.resize(N);
        }

        { // DFS
            Timer timer("DFSes");
            dfs1(root);
            dfs2(root);
        }

        { // Table Building
            Timer timer("Table Building");
            for (int n = 0; n < N; n++) {
                table[n] = (parent[hldOrder[n]] == -1 ? -1 : hldId[parent[hldOrder[n]]]);
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


    void dfs1(int root) {
        stk[0] = root;
        stkPtr = 0;
        size[root] = 1;
        while (stkPtr >= 0) {
            int n = stk[stkPtr];
            bool toPop = true;
            while (dfsPtr[n] < graph[n].size()) {
                int i = dfsPtr[n];
                dfsPtr[n]++;
                if (graph[n][i] != parent[n]) {
                    int e = graph[n][i];
                    parent[e] = n;
                    stkPtr++;
                    stk[stkPtr] = e;
                    toPop = false;
                    size[e] = 1;
                    break;
                }
            }
            if (toPop) {
                stkPtr--;
                if (stkPtr < 0) {
                    continue;
                }
                int p = parent[n];
                size[p] += size[n];
                if (heavyChild[p] == -1 || size[n] > size[heavyChild[p]]) {
                    heavyChild[p] = n;
                }
            }
        }
    }

    
    void dfs2(int root) {
        fill(dfsPtr.begin(), dfsPtr.end(), 0);
        stk[0] = root;
        stkPtr = 0;
        hldOrder[C++] = root;
        hldId[root] = 0;
        while (stkPtr >= 0) {
            int n = stk[stkPtr];
            bool toPop = true;
            if (!doneHeavyChild[n] && heavyChild[n] != -1) {
                stk[++stkPtr] = heavyChild[n];
                hldId[heavyChild[n]] = C;
                hldOrder[C++] = heavyChild[n];
                doneHeavyChild[n] = true;
                continue;
            }
            while (dfsPtr[n] < graph[n].size()) {
                int i = dfsPtr[n];
                dfsPtr[n]++;
                if (graph[n][i] != parent[n] && graph[n][i] != heavyChild[n]) {
                    int e = graph[n][i];
                    hldId[e] = C;
                    hldOrder[C++] = e;
                    stkPtr++;
                    stk[stkPtr] = e;
                    toPop = false;
                    break;
                }
            }
            if (toPop) {
                stkPtr--;
            }
        }
    }


    int query(int n, int k) {
        int ancestor = hldId[n];
        while (k != 0) {
            int d = 31 - __builtin_clz(k);
            ancestor = table[d * N + ancestor];
            k ^= (1 << d);
        }
        return hldOrder[ancestor];
    }


    int D;
    int N;
    int C;
    int stkPtr;
    std::vector<int> dfsPtr;
    std::vector<int> stk;
    std::vector<int> parent;
    std::vector<int> hldId;
    std::vector<int> hldOrder;
    std::vector<int> heavyChild;
    std::vector<int> doneHeavyChild;
    std::vector<int> size;
    std::vector<std::vector<int>> graph;
    std::vector<int> table;
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

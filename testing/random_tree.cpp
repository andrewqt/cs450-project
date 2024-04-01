#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    int q = atoi(argv[2]);
    mt19937 seed(atoi(argv[3]));
    if (argc >= 5) {
        freopen(argv[4], "w", stdout);
    }
    cout << n << "\n";
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int rnd = uniform_int_distribution<int>(0, i - 1)(seed);
        pair<int, int> edge = make_pair(i, rnd);
        if (uniform_int_distribution<int>(0, 1)(seed)) {
            swap(edge.first, edge.second);
        }
        edges.push_back(edge);
    }
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    for (int i = n - 1; i >= 0; i--) {
        int j = uniform_int_distribution<int>(0, i)(seed);
        std::swap(perm[i], perm[j]);
    }
    
    vector<vector<int>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        std::cout << perm[edges[i].first] << " " << perm[edges[i].second] << "\n";
        graph[perm[edges[i].first]].push_back(perm[edges[i].second]);
        graph[perm[edges[i].second]].push_back(perm[edges[i].first]);
    }

    vector<int> dep(n);
    vector<int> stk(n);
    vector<int> par(n, -1);
    int stkPtr = 0;
    stk[stkPtr] = 0;
    while(stkPtr >= 0) {
        int n = stk[stkPtr];
        stkPtr--;
        for (int e : graph[n]) {
            if (e != par[n]) {
                stkPtr++;
                stk[stkPtr] = e;
                par[e] = n;
                dep[e] = dep[n] + 1;
            }
        }
    }

    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int a = uniform_int_distribution<int>(0, n - 1)(seed);
        int b = uniform_int_distribution<int>(0, dep[a])(seed);
        cout << a << " " << b << "\n";
    }
}

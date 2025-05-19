#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max() / 4;

// Собственная реализация min-кучи для пар (distance, vertex)
struct MinHeap {
    vector<pair<ll, int>> h;

    void push(pair<ll, int> x) {
        h.push_back(x);
        int i = (int)h.size() - 1;
        while (i > 0) {
            int p = (i - 1) / 2;
            if (h[p].first <= h[i].first) break;
            swap(h[p], h[i]);
            i = p;
        }
    }

    bool empty() const {
        return h.empty();
    }

    pair<ll, int> top() const {
        return h[0];
    }

    void pop() {
        int n = (int)h.size();
        if (n == 0) return;
        h[0] = h[n - 1];
        h.pop_back();
        n--;
        int i = 0;
        while (true) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            if (l >= n) break;
            int smallest = l;
            if (r < n && h[r].first < h[l].first) smallest = r;
            if (h[smallest].first >= h[i].first) break;
            swap(h[i], h[smallest]);
            i = smallest;
        }
    }
};

int main() {
    // Открываем файлы
    ifstream fin("input_18_5.txt");
    ofstream fout("output_18_5.txt");

    if (!fin) {
        return 1;
    }
    if (!fout) {
        return 1;
    }

    int N, M, S, T;
    fin >> N >> M >> S >> T;

    vector<vector<pair<int, int>>> adj(N + 1);
    for (int k = 0; k < M; k++) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    vector<ll> dist(N + 1, INF);
    vector<int> parent(N + 1, -1);
    dist[S] = 0;

    MinHeap pq;
    pq.push({ 0, S });

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        ll d = cur.first;
        int u = cur.second;
        if (d != dist[u]) continue;
        if (u == T) break;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    if (dist[T] == INF) {
        fout << "No";
        return 0;
    }

    fout << dist[T] << "\n";

    vector<int> path;
    for (int v = T; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    for (int i = (int)path.size() - 1; i >= 0; --i) {
        fout << path[i] << (i ? ' ' : '\n');
    }

    return 0;
}

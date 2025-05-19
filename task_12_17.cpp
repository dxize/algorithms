#include <iostream>
#include <vector>
#include <queue>

const int MAXN = 2005;

// Граф G — исходные знакомства, H — расширенный граф
std::vector<int> G[MAXN], H[MAXN];
// Массив для Union-Find
int parent[MAXN];

// Инициализация множества
void make_set(int v) {
    parent[v] = v;
}

// Поиск корня множества с сжатием пути
int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

// Объединение множеств
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) parent[b] = a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Ввод данных
    int N, M;
    std::cin >> N >> M;
    int u, v;
    std::cin >> u >> v;

    // Инициализация Union-Find
    for (int i = 1; i <= N; i++) {
        make_set(i);
    }

    // Построение графа G
    for (int i = 0; i < M; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
        union_sets(a, b);
    }

    // Проверка связности
    if (find_set(u) != find_set(v)) {
        std::cout << -1 << std::endl;
        return 0;
    }

    // Проверка прямой связи
    bool directly_connected = false;
    for (int w : G[u]) {
        if (w == v) {
            directly_connected = true;
            break;
        }
    }
    if (directly_connected) {
        std::cout << 0 << std::endl;
        return 0;
    }

    // Построение графа H
    // Добавляем рёбра между всеми парами, у которых есть общий сосед в G
    for (int w = 1; w <= N; w++) {
        for (int x : G[w]) {
            for (int y : G[w]) {
                if (x != y) {
                    H[x].push_back(y);
                }
            }
        }
    }
    // Добавляем оригинальные рёбра из G в H
    for (int i = 1; i <= N; i++) {
        for (int j : G[i]) {
            H[i].push_back(j);
        }
    }
    // Удаляем дубликаты в списках смежности H вручную
    for (int i = 1; i <= N; i++) {
        std::vector<int> temp;
        for (int j : H[i]) {
            // Используем std::find для поиска элемента в temp
            if (std::find(temp.begin(), temp.end(), j) == temp.end()) {
                temp.push_back(j);
            }
        }
        H[i] = temp;
    }

    // BFS в H, начиная с соседей u
    std::vector<int> distance(N + 1, -1);
    std::queue<int> q;
    for (int w : G[u]) {
        distance[w] = 0;
        q.push(w);
    }
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (int x : H[w]) {
            if (distance[x] == -1) {
                distance[x] = distance[w] + 1;
                q.push(x);
                if (x == v) {
                    std::cout << distance[x] << std::endl;
                    return 0;
                }
            }
        }
    }

    // Если v не достигнут (хотя это не должно произойти, если они в одной компоненте)
    std::cout << -1 << std::endl;
    return 0;
}

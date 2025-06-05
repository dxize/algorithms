//12.17.Клуб знакомств(5)
//В студенческом клубе знакомств состоит N человек, которым присвоены номера от 1 до N.При организации клуба каждый представил список своих знакомых.По воскресениям проводятся вечера знакомств, когда знакомые любого студента знакомятся между собой.Выяснить, через сколько воскресений познакомятся два указанных члена клуба.
//Ввод.В первой строке заданы число членов клуба N(2 ≤ N ≤ 2000) и количество попарных знакомств M.Во второй строке содержатся номера двух студентов.Каждая из следующих M строк, начиная с третьей, описывает знакомство в виде двух номеров студентов.
//Вывод.Вывести количество воскресений, необходимых для знакомства двух указанных студентов.Если знакомство невозможно, вывести - 1.
//Примеры
//Ввод 1       Ввод 2       Ввод 3
//5 4          3 3          4 2
//1 5          1 3          4 1
//1 2          1 2          1 2
//2 3          2 3          3 4
//3 4          3 1
//4 5
//Вывод 1      Вывод 2      Вывод 3
//2            0 - 1
//Пояснение.В примере 1 после первого воскресения познакомятся студенты 1 и 3, поскольку у них имеется общий знакомый 2. Аналогично познакомятся 2 и 4, 3 и 5. Во второе воскресение познакомятся студенты 1 и 5, т.к.у них после первого воскресения есть общий знакомый 3. В примере 2 студенты 1 и 3 уже знакомы.
//
//
//Дмитриев Данил ПС-21



#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    int u, v;
    cin >> u >> v;

    vector<vector<int>> G(N + 1); 

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    for (int x : G[u]) {
        if (x == v) {
            cout << 0 << endl;
            return 0;
        }
    }

    vector<bool> visited(N + 1, false);
    queue<int> q1;
    q1.push(u);
    visited[u] = true;
    bool reachable = false;
    while (!q1.empty()) {
        int curr = q1.front(); q1.pop();
        if (curr == v) {
            reachable = true;
            break;
        }
        for (int neighbor : G[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q1.push(neighbor);
            }
        }
    }
    if (!reachable) {
        cout << -1 << endl;
        return 0;
    }

    vector<set<int>> H(N + 1);
    for (int w = 1; w <= N; ++w) {
        for (int a : G[w]) {
            for (int b : G[w]) {
                if (a != b) {
                    H[a].insert(b); // знакомятся через w
                }
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j : G[i]) {
            H[i].insert(j);
        }
    }

    vector<int> dist(N + 1, -1);
    queue<int> q;
    for (int x : G[u]) {
        dist[x] = 0;
        q.push(x);
    }

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        for (int neighbor : H[curr]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[curr] + 1;
                if (neighbor == v) {
                    cout << dist[neighbor] << endl;
                    return 0;
                }
                q.push(neighbor);
            }
        }
    }

    cout << -1 << endl;
    return 0;
}

//22. Задан взвешенный ориетированный граф.С помощью алгоритма
//Беллмана - Форда найти кратчайший путь между заданными вершинами.
//Проверить наличие циклов отрицательной длины.В случае обнаружения
//вывести один из них(10).



#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>


struct Vertex {
    std::string name;
    int distance;
    Vertex* prev;

    Vertex(const std::string& name) : name(name), distance(1000000), prev(nullptr) {}
};

struct Edge {
    std::string from;
    std::string to;
    int weight;

    Edge(const std::string& from, const std::string& to, int weight) : from(from), to(to), weight(weight) {}
};

void addEdge(std::vector<Vertex>& vertices, std::vector<Edge>& edges, const std::string& from, const std::string& to, int weight) {
    edges.emplace_back(from, to, weight);

    bool fromExists = false, toExists = false;
    for (const auto& vertex : vertices) {
        if (vertex.name == from) fromExists = true;
        if (vertex.name == to) toExists = true;
    }
    if (!fromExists) vertices.emplace_back(from);
    if (!toExists) vertices.emplace_back(to);
}

Vertex* findVertex(std::vector<Vertex>& vertices, const std::string& name) {
    for (auto& vertex : vertices) {
        if (vertex.name == name) return &vertex;
    }
    return nullptr;
}

void printNegativeCycle(Vertex* start) {
    // Используем slow/fast указатели для нахождения цикла
    Vertex* slow = start;
    Vertex* fast = start;

    // Двигаемся "быстро" до нахождения цикла
    for (int i = 0; i < 1000; i++) {  // Ограничиваем число итераций
        if (!fast || !fast->prev) return;  // На случай ошибок
        slow = slow->prev;
        fast = fast->prev->prev;

        if (slow == fast) break;
    }

    // Если цикл найден, строим его
    std::vector<std::string> cycle;
    Vertex* current = slow;

    do {
        cycle.push_back(current->name);
        current = current->prev;
    } while (current != slow);

    std::cout << "Найден цикл отрицательной длины: ";
    for (int i = cycle.size() - 1; i >= 0; i--) {
        std::cout << cycle[i] << " ";
    }
    std::cout << cycle[cycle.size() - 1] << "\n";
}

void printShortestPath(Vertex* endVertex) {
    if (endVertex->distance == 1000000) {
        std::cout << "Кратчайший путь недостижим\n";
        return;
    }

    std::vector<std::string> path;
    for (Vertex* v = endVertex; v != nullptr; v = v->prev) {
        path.push_back(v->name);
    }

    std::cout << "Кратчайший путь: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << (i > 0 ? " -> " : "\n");
    }
    std::cout << "С общей длиной: " << endVertex->distance << "\n";
}

void bellmanFord(std::vector<Vertex>& vertices, std::vector<Edge>& edges, const std::string& start, const std::string& end) {
    Vertex* startVertex = findVertex(vertices, start);
    Vertex* endVertex = findVertex(vertices, end);

    if (startVertex) startVertex->distance = 0;

    // Основной цикл Беллмана-Форда
    for (int i = 0; i < vertices.size() - 1; i++) {
        for (const auto& edge : edges) {
            Vertex* u = findVertex(vertices, edge.from);
            Vertex* v = findVertex(vertices, edge.to);

            if (u && v && u->distance != 1000000 && u->distance + edge.weight < v->distance) {
                v->distance = u->distance + edge.weight;
                v->prev = u;
            }
        }
    }

    // Проверка на отрицательные циклы
    for (const auto& edge : edges) {
        Vertex* u = findVertex(vertices, edge.from);
        Vertex* v = findVertex(vertices, edge.to);

        if (u && v && u->distance != 1000000 && u->distance + edge.weight < v->distance) {

            // Ищем начало цикла
            Vertex* cycleStart = v;
            for (int j = 0; j < vertices.size(); j++) {
                if (cycleStart->prev) cycleStart = cycleStart->prev;
            }
            printNegativeCycle(cycleStart);
            return;
        }
    }

    // Если нет отрицательного цикла, выводим кратчайший путь
    if (endVertex) {
        printShortestPath(endVertex);
    }
}

void readGraph(const std::string& fileName, std::vector<Vertex>& vertices, std::vector<Edge>& edges, bool& can) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл.\n";
        can = false;
        return;
    }

    std::string from, to;
    int weight;
    while (file >> from >> to >> weight) {
        addEdge(vertices, edges, from, to, weight);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string choice;
    bool can;

    do {
        can = true;
        std::cout << "[1] - Начать поиск/Запустить заново\n[Любая клавиша, кроме '1'] - Завершить программу\n";
        std::cin >> choice;
        if (choice == "1") {
            std::string fileName;
            std::cout << "Введите имя файла с графом: ";
            std::cin >> fileName;

            std::vector<Vertex> vertices;
            std::vector<Edge> edges;
            readGraph(fileName, vertices, edges, can);
            if (can) {
                std::string startVertex;
                std::string endVertex;
                std::cout << "Введите начальную вершину: ";
                std::cin >> startVertex;
                std::cout << "Введите конечную вершину: ";
                std::cin >> endVertex;

                bellmanFord(vertices, edges, startVertex, endVertex);
            }
        }
    } while (choice == "1");

    return 0;
}

//22. ����� ���������� �������������� ����.� ������� ���������
//�������� - ����� ����� ���������� ���� ����� ��������� ���������.
//��������� ������� ������ ������������� �����.� ������ �����������
//������� ���� �� ���(10).



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
    // ���������� slow/fast ��������� ��� ���������� �����
    Vertex* slow = start;
    Vertex* fast = start;

    // ��������� "������" �� ���������� �����
    for (int i = 0; i < 1000; i++) {  // ������������ ����� ��������
        if (!fast || !fast->prev) return;  // �� ������ ������
        slow = slow->prev;
        fast = fast->prev->prev;

        if (slow == fast) break;
    }

    // ���� ���� ������, ������ ���
    std::vector<std::string> cycle;
    Vertex* current = slow;

    do {
        cycle.push_back(current->name);
        current = current->prev;
    } while (current != slow);

    std::cout << "������ ���� ������������� �����: ";
    for (int i = cycle.size() - 1; i >= 0; i--) {
        std::cout << cycle[i] << " ";
    }
    std::cout << cycle[cycle.size() - 1] << "\n";
}

void printShortestPath(Vertex* endVertex) {
    if (endVertex->distance == 1000000) {
        std::cout << "���������� ���� ����������\n";
        return;
    }

    std::vector<std::string> path;
    for (Vertex* v = endVertex; v != nullptr; v = v->prev) {
        path.push_back(v->name);
    }

    std::cout << "���������� ����: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << (i > 0 ? " -> " : "\n");
    }
    std::cout << "� ����� ������: " << endVertex->distance << "\n";
}

void bellmanFord(std::vector<Vertex>& vertices, std::vector<Edge>& edges, const std::string& start, const std::string& end) {
    Vertex* startVertex = findVertex(vertices, start);
    Vertex* endVertex = findVertex(vertices, end);

    if (startVertex) startVertex->distance = 0;

    // �������� ���� ��������-�����
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

    // �������� �� ������������� �����
    for (const auto& edge : edges) {
        Vertex* u = findVertex(vertices, edge.from);
        Vertex* v = findVertex(vertices, edge.to);

        if (u && v && u->distance != 1000000 && u->distance + edge.weight < v->distance) {

            // ���� ������ �����
            Vertex* cycleStart = v;
            for (int j = 0; j < vertices.size(); j++) {
                if (cycleStart->prev) cycleStart = cycleStart->prev;
            }
            printNegativeCycle(cycleStart);
            return;
        }
    }

    // ���� ��� �������������� �����, ������� ���������� ����
    if (endVertex) {
        printShortestPath(endVertex);
    }
}

void readGraph(const std::string& fileName, std::vector<Vertex>& vertices, std::vector<Edge>& edges, bool& can) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����.\n";
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
        std::cout << "[1] - ������ �����/��������� ������\n[����� �������, ����� '1'] - ��������� ���������\n";
        std::cin >> choice;
        if (choice == "1") {
            std::string fileName;
            std::cout << "������� ��� ����� � ������: ";
            std::cin >> fileName;

            std::vector<Vertex> vertices;
            std::vector<Edge> edges;
            readGraph(fileName, vertices, edges, can);
            if (can) {
                std::string startVertex;
                std::string endVertex;
                std::cout << "������� ��������� �������: ";
                std::cin >> startVertex;
                std::cout << "������� �������� �������: ";
                std::cin >> endVertex;

                bellmanFord(vertices, edges, startVertex, endVertex);
            }
        }
    } while (choice == "1");

    return 0;
}

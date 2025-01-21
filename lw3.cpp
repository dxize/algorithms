//12. Имеется   дерево, корень    которого    соответствует
//основателю  рода.Сыновья  каждой  вершины  задают  сыновей и
//дочерей  соответствующего  человека.Указываются  имена  двух
//человек(например, А  и  В).Сообщить, какая  из следующих
//ситуаций имеет место :
//1) А предок В;
//2) В предок А;
//3) А и В имеют ближайшего общего предка С(9).

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

struct Tree {
    std::string name;
    int lvl;
    Tree* left, * right, *prev;
};

void getPersons(std::string& first, std::string& second, const std::string& search) {
    int i = 0;
    bool forFirst = true;

    while (i < search.length()) {

        if (search[i] == ' ') {
            i++;
            continue;
        }

        if (search[i] == '<' || search[i] == '-' || search[i] == '>') {
            forFirst = false;
            i++;
            continue;
        }

        if (forFirst) {
            first += search[i];
        }
        else {
            second += search[i];
        }

        i++;
    }
}
bool isAncestor(Tree* ancestor, Tree* descendant, Tree* parents[]) {
    bool may{ true };
    while (true) {

        if (ancestor == parents[1]) {
            return true;
        }
        else {
            if (descendant->lvl != 0) {
                descendant = descendant->prev;
                if (descendant->lvl == 0) {
                    may = false;
                }
            }
        }
        if (ancestor == descendant && parents[1]->lvl >= descendant->lvl) {
            return true;
        }
        if (descendant->lvl == 0 && may) {
            return false;
        }
        may = true;
    }
}




// Функция поиска общего предка
Tree* findCommonAncestor(Tree* firstParent, Tree* secondParent) {
    while (firstParent->lvl > secondParent->lvl) {
        firstParent = firstParent->prev; 
    }
    while (secondParent->lvl > firstParent->lvl) {
        secondParent = secondParent->prev; 
    }


    while (firstParent != nullptr && secondParent != nullptr) {
        if (firstParent == secondParent) {
            return firstParent; 
        }
        if (firstParent->lvl != 0) {
            firstParent = firstParent->prev;
        }
        if (secondParent->lvl != 0) {
            secondParent = secondParent->prev;
        }
    
    }

    // Если не нашли общего предка
    return nullptr;
}

std::string findParents(Tree*& first, Tree*& second, Tree*& ptr, int& foundCount, Tree* parents[], bool& can) {
    int i{ 0 };
    if (ptr->name == first->name || ptr->name == second->name) {
        if (foundCount == 0) {
            if (ptr->name == first->name) {
                first = ptr;
            }
            else if (ptr->name == second->name) {
                second = first;
                first = ptr;
            }
            can = false;
            foundCount++;
        }
        else if (foundCount == 1 && ptr != first) {
            second = ptr;
            can = false;
            foundCount++;
        }
    }
    while (i != 2 && can) {

        if (ptr->left != nullptr && foundCount < 2 && can) {
            findParents(first, second, ptr->left, foundCount, parents, can);
        }
        if (ptr->right != nullptr && foundCount < 2 && can) {
            findParents(first, second, ptr->right, foundCount, parents, can);
        }
        i++;

    }
 
    if (!can && ptr->lvl < first->lvl && foundCount < 2) {
        can = true;
        parents[0] = ptr;
    }
    else if (!can && ptr->lvl < second->lvl) {
        can = true;
        parents[1] = ptr;
    }
    else if(!can && ptr->lvl == 0) {
        can = true;
        if (foundCount = 1) {
            parents[0] = ptr;
        }
        else if(foundCount = 2) {
            parents[1] = ptr;
        }
    }

    if (foundCount == 2 && parents[1] != nullptr && parents[0] != nullptr) {
        // Если first — предок second
        if (isAncestor(first, second, parents)) {
            return first->name + " является предком " + second->name + "\n";
        }
        // Если second — предок first
        else if (isAncestor(second, first, parents)) {
            return second->name + " является предком " + first->name + "\n";
        }
        // Ищем общего предка
        else {
            Tree* commonAncestor = findCommonAncestor(parents[0], parents[1]);
            if (commonAncestor != nullptr) {
                return first->name + " и " + second->name + " имеют общего предка: " + commonAncestor->name + "\n";
            }
        }
    }

    if (ptr->lvl == 0 && foundCount != 2) {
        return findParents(first, second, ptr, foundCount, parents, can);
    }
    else {
        return "";
    }

   
}

// Чтение дерева из файла
void creatNode(Tree*& ptr, std::string& curr, std::string& imageTree, Tree* prev = nullptr) {
    int i = 0;

    if (ptr == nullptr) {
        ptr = new Tree;
        ptr->prev = prev;  

        if (curr[i] != '.') {
            ptr->lvl = i;
            ptr->name = curr;
        }
        else if (curr[i] == '.') {
           while (curr[i] == '.') {
                i++;
            }
            ptr->lvl = i;
            while (i != curr.length()) {
                ptr->name += curr[i];
                i++;
            }
        }
        ptr->left = nullptr;
        ptr->right = nullptr;
        imageTree += curr + "\n";
    }
    else if (curr[i] == '.') {
        while (curr[i] == '.') {
            i++;
        }
        if (ptr->lvl < i && ptr->right == nullptr) {
            creatNode(ptr->left, curr, imageTree, ptr);
        }
        else {
            creatNode(ptr->right, curr, imageTree, ptr);
        }
    }
}

std::string readFromFile(const std::string& fileName, Tree*& root) {
    std::ifstream file(fileName);
    std::string imageTree;
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл.\n";
        return "false";
    }

    std::string line;
    while (std::getline(file, line)) {
        creatNode(root, line, imageTree);
    }
    return imageTree;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string fileName;
    char startChoice;
    std::string imageTree;
    bool firstTry{ true };
    std::string search;
    std::string relationship;
    char ch;
    Tree* root;
    Tree* parents[2];
    bool can;
    int i;

    do {
        can = true;
        root = nullptr;
        parents[0] = nullptr;
        parents[1] = nullptr;
        if (firstTry) {
            std::cout << "Введите имя файла с деревом: ";
            std::cin >> fileName;
        }
        imageTree = readFromFile(fileName, root);

        if (imageTree != "false") {
            std::cout << "[1] - Ввести данные для поиска\n[2] - Вывести исходное дерево\n[3] - Завершить программу\n";
            std::cin >> startChoice;
            std::cin.get(ch);
        }
        else {
            startChoice = '3';
        }
        if (startChoice == '1') {
            i = 0;
            search = "";
            std::cout << "Формат запроса: 'A <-> B'\nГде 'A' это первый объект поиска, 'B' второй соответственно\n";
            while (std::cin.get(ch) && ch != '\n') {
                search += ch;
            }
            Tree* firstPerson = new Tree;
            Tree* secondPerson = new Tree;
   
            getPersons(firstPerson->name, secondPerson->name, search);
            if (root != nullptr) {
                relationship = findParents(firstPerson, secondPerson, root, i, parents, can);
                std::cout << relationship;
            }
            else {
                std::cout << "Пустое дерево\n";
            }
            delete firstPerson;
            delete secondPerson;
        }
        else if (startChoice == '2') {
            std::cout << imageTree << "\n";
        }
        else if (startChoice == '3') {
            std::cout << "Программа завершена\n";
        }
        firstTry = false;

    } while (startChoice == '1' || startChoice == '2');

    return 0;
}
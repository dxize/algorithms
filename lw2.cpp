//В строке текстового файла  задано  выражение  из  целых 
//чисел и операций '+', '-', '*', '/', '^', SIN, COS, EXP.Порядок
//вычислений  определяется  приоритетом  операций   и   круглыми
//скобками.Возможен одноместный минус в  начале  выражения  или
//после открывающей скобки.Преобразовать выражение в постфиксную
//форму(алгоритм Дейкстры) и вычислить его  значение.Показать
//этапы  выполнения(11).s

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath> // Для математических функций
#include <Windows.h>

struct St {
    std::string key;
    St* next;
};

int priority(const std::string& elem) {
    if (elem == "^") return 3;
    if (elem == "*" || elem == "/") return 2;
    if (elem == "+" || elem == "-") return 1;
    return 0;
}

bool isEmpty(St* stack) {
    return (stack == nullptr);  // Если стек пуст, указатель на вершину равен nullptr
}

bool isOperand(const std::string& str) {
    if (str[0] == '-') {
        if (str.length() == 1) {
            return false; // Только "-" не является числом
        }
        for (size_t i = 1; i < str.length(); ++i) {
            if (!std::isdigit(str[i])) {
                return false; 
            }
        }
        return true; 
    }
    else if ((std::isalpha(str[0]) || std::isdigit(str[0])) && str != "cos" && str != "sin" && str != "exp" && str != "ln") {
        return true;
    }
    return false;
}

bool characterForStack(const std::string& str) {
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "^" ||
        str == "sin" || str == "cos" || str == "exp" || str == "ln";
}

void push(St*& head, const std::string& elem) {
    St* newptr = new St;
    newptr->key = elem;
    newptr->next = head;
    head = newptr;
}

void pop(St*& head) {
    if (head != nullptr) {
        St* temp = head;
        head = head->next;
        delete temp;
    }
}

std::string top(St* head) {
    if (head != nullptr && head->key != "") {
        return head->key;
    }
    return "";
}

void processOperator(St*& head, const std::string& token, std::string& postfix) {
    while (head != nullptr && ((token != "^" && token != "sin" && token != "cos" && token != "exp" && token != "ln" && priority(top(head)) >= priority(token)))) {
        postfix += top(head) + " ";
        pop(head);
    }
    push(head, token);
}



void processRightParenthesis(St*& head, std::string& postfix) {
    while (head != nullptr && top(head) != "(") {
        postfix += top(head) + " ";
        pop(head);
    }
    pop(head); 
}

bool processExpression(std::stringstream& input, std::string& postfix) {
    St* stack = nullptr;
    char ch{ ' ' };
    std::string token{ "" };
    char prevCh{ ' ' };
    bool unaryMinus{ false };

    while (input.get(ch)) {
        if (ch == 's') {
            token += ch;
            if (!input.get(ch)) {  // Проверяем, не закончился ли поток
                postfix += token + " ";  
                token = "";
                break;
            }
            if (ch == 'i') {
                token += ch;
                input.get(ch);
                if (ch == 'n') {
                    token += ch;
                }
                else if(ch != '(' && ch != ')' && ch != ' ') {
                    std::cout << "Ошибка\n\n";
                    return false;
                }
            }
            else if (ch != '(' && ch != ')' && ch != ' ') {
                std::cout << "Ошибка\n\n";
                return false;
            }
        }
        else if (ch == 'c') {
            token += ch;
            if (!input.get(ch)) {  // Проверяем, не закончился ли поток
                postfix += token + " ";  
                token = "";
                break;
            }
            if (ch == 'o') {
                token += ch;
                input.get(ch);
                if (ch == 's') {
                    token += ch;
                }
                else if (ch != '(' && ch != ')' && ch != ' ') {
                    std::cout << "Ошибка\n\n";
                    return false;
                }
            }
            else if (ch != '(' && ch != ')' && ch != ' ') {
                std::cout << "Ошибка\n\n";
                return false;
            }
        }
        else if (ch == 'e') {
            token += ch;
            if (!input.get(ch)) {  // Проверяем, не закончился ли поток
                postfix += token + " ";  
                token = "";
                break;
            }
            if (ch == 'x') {
                token += ch;
                input.get(ch);
                if (ch == 'p') {
                    token += ch;
                }
                else if (ch != '(' && ch != ')' && ch != ' ') {
                    std::cout << "Ошибка\n\n";
                    return false;
                }
            }
            else if (ch != '(' && ch != ')' && ch != ' ') {
                std::cout << "Ошибка\n\n";
                return false;
            }
        }
        else if (ch == 'l') {
            token += ch;
            if (!input.get(ch)) {  // Проверяем, не закончился ли поток
                postfix += token + " ";  
                token = "";
                break;
            }
            if (ch == 'n') {
                token += ch;
            }
            else if (ch != '(' && ch != ')' && ch != ' ') {
                std::cout << "Ошибка\n\n";
                return false;
            }
        }
        else if (ch == ' '){ 
            continue;
        }
        else if (ch == '-' && (prevCh == '(' || prevCh == ' ')) {
            
            while (input.peek() != EOF && std::isdigit(input.peek())) {
                input.get(ch);
                token += ch;
            }
            if (ch != '-') {
                postfix += token + " - ";
                token = "";
            }
            else {
                token = ch;
            }
        }

        else {
            if (token.length() > 1 && !unaryMinus) {
                std::cout << "Ошибка\n\n";
                return false;
            }
            else if (std::isdigit(ch)){
                token += ch;
                while (input.peek() != EOF && (std::isdigit(input.peek()) || input.peek() == '.')) {
                    input.get(ch);
                    token += ch;
                }
                postfix += token + " ";
                token = "";
            }
            else {
                token += ch;
            }
        }
        
        if (ch == '(') {
            push(stack, "("); 
            token = "";    
        }
        else if (ch == ')') {
            if (isOperand(token)) {
                postfix += token + " ";
            }
            processRightParenthesis(stack, postfix);  // Обрабатываем всё внутри скобок
            token = "";
        }
        else if (characterForStack(token)) {
            processOperator(stack, token, postfix);
            token = "";
        }
        else if (isOperand(token)) {
            postfix += token + " ";
            token = "";
        }
        prevCh = ch;
        unaryMinus = false;
    }

    while (stack != nullptr) {
        postfix += top(stack) + " ";
        pop(stack);
    }
    return true;
}

// Функция для преобразования строки в число
double toNumber(const std::string& str) {
    std::istringstream iss(str);
    double num;
    iss >> num;
    return num;
}

double evaluatePostfix(const std::string& postfix) {
    std::stringstream ss(postfix);
    std::string token;
    St* stack = nullptr;

    while (ss >> token) {
        if (isOperand(token)) {
            push(stack, token);
        }
        else 
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
                double b = toNumber(top(stack));  // Второй операнд
                pop(stack);

                // Унарный минус
                if (token == "-" && isEmpty(stack)) {
                    push(stack, std::to_string(-b));
                }
                else {
                    double a = toNumber(top(stack));  // Первый операнд
                    pop(stack);

                    double result = 0;
                    if (token == "+") result = a + b;
                    else if (token == "-") result = a - b;
                    else if (token == "*") result = a * b;
                    else if (token == "/") result = a / b;
                    else if (token == "^") result = pow(a, b);

                    push(stack, std::to_string(result));  
                }
            }
            else if (token == "sin" || token == "cos" || token == "exp" || token == "ln") {
                double a = toNumber(top(stack));  // Операнд для функций
                pop(stack);
                double result = 0;

                if (token == "sin") result = sin(a);
                else if (token == "cos") result = cos(a);
                else if (token == "exp") result = exp(a);
                else if (token == "ln") result = log(a);

                push(stack, std::to_string(result)); 
            }
        }
    
    double finalResult = toNumber(top(stack));
    pop(stack);
    return finalResult;
}



void readFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream input(line);
        std::string postfix;
        bool finish{ true };
        std::cout << "Инфиксная форма: " << line << "\n";
        finish = processExpression(input, postfix);
        if (finish) {
            std::cout << "Постфиксная форма: " << postfix << "\n";
            double result = evaluatePostfix(postfix); // Вычисляем результат
            std::cout << "Результат: " << result << "\n\n";
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string fileName;
    char choice;

    do {
        std::cout << "Введите имя файла с математическими выражениями: ";
        std::cin >> fileName;

        readFromFile(fileName);

        std::cout << "Хотите обработать другой файл? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

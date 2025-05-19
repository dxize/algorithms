#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool ReadFromFile(const string& filename, vector<int>& numbers) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    int n;
    if (!(file >> n) || n < 2) return false;

    numbers.resize(n);
    for (int i = 0; i < n; ++i) {
        if (!(file >> numbers[i])) return false;
    }
    return true;
}

void CalculateResult(const vector<int>& numbers, long long& result, vector<int>& operations) {
    vector<int> temp = numbers;
    operations.clear();
    int amountMinus = 0; 
    bool can = false;
    int flagForReverse = 0;
    bool isReverse = true;

    // Обработка положительных элементов справа налево
    for (int i = 0; i + 1 < temp.size(); ++i)
    {
        if (can) 
        {
            if (i != 0 && temp[i] < 0)
            {
                // Объединяем текущий элемент с предыдущим
                temp[i] -= temp[i + 1];
                operations.push_back(i); // Сохраняем операцию (1-based индекс)
                temp.erase(temp.begin() + i + 1);
                --amountMinus;
            }
            else if (i != 0 && amountMinus == 0 && temp[i] < temp[i + 1])
            {
                temp[i] -= temp[i + 1];
                operations.push_back(i); // Сохраняем операцию (1-based индекс)
                temp.erase(temp.begin() + i + 1);
            }
            else
            {
                ++flagForReverse;
            }
        }

        if (temp[i + 1] < 0 && !can)
        {
            ++amountMinus;
        }
        if (i + 2 >= temp.size() && !can)
        {
            i = -1;
            can = true;
        }

        if (flagForReverse == temp.size())
        {
            isReverse = false;
        }
    }

    if (isReverse)
    {
        for (int i = temp.size() - 1; i > 0; --i) {
            temp[i - 1] -= temp[i];
            operations.push_back(i); 
            temp.erase(temp.begin() + i);
        }
    }
    else
    {// Обработка оставшихся элементов слева направо
        while (temp.size() > 1) {
            temp[0] -= temp[1];
            operations.push_back(1);
            temp.erase(temp.begin() + 1);
        }
    }

    result = temp[0];
}

void PrintResults(long long result, const vector<int>& operations) {
    cout << result << "\n";
    for (size_t i = 0; i < operations.size(); ++i) {
        cout << operations[i] << (i < operations.size() - 1 ? " " : "");
    }
    cout << "\n";
}

int main() {
    string filename;
    vector<int> numbers;
    long long result;
    vector<int> operations;

    cout << "Введите имя файла: ";
    cin >> filename;

    if (!ReadFromFile(filename, numbers)) {
        cerr << "Ошибка чтения файла или некорректные данные!\n";
        return 1;
    }

    CalculateResult(numbers, result, operations);
    PrintResults(result, operations);

    return 0;
}
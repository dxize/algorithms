//15.2.Спички(4)
//Вася и Петя любят следующую игру.Два игрока поочередно забирают из кучки, содержащей N спичек, либо A, либо B спичек(1 ≤ A, B ≤ N ≤ 105).Игрок проигрывает, если необходимого для хода количества спичек не оказывается.Игру начинает Вася.Кто выиграет при правильной игре с обеих сторон ?
//Ввод из файла INPUT.TXT.В единственной строке содержатся значения N, A, B.
//Вывод в файл OUTPUT.TXT.В единственной строке выводится значение 1, если выигрывает Вася, либо 2 в случае выигрыша Пети.
//Примеры
//Ввод 1          Ввод 2
//14 3 5          15 2 1
//Вывод 1         Вывод 2
//1
//
//Дмитриев Данил ПС-21

#include <fstream>
#include <vector>

using namespace std;

bool canWin(int matches, int take1, int take2) {
    vector<bool> result(matches + 1, false);

    for (int i = 1; i <= matches; ++i) {
        bool option1 = (i >= take1) ? !result[i - take1] : false;
        bool option2 = (i >= take2) ? !result[i - take2] : false;
        result[i] = option1 || option2;
    }

    return result[matches];
}

int main() {
    ifstream input("input_15_2.txt");
    ofstream output("output_15_2.txt");

    if (!input || !output) return 1;

    int total, move1, move2;
    input >> total >> move1 >> move2;

    output << (canWin(total, move1, move2) ? 1 : 2) << endl;

    return 0;
}
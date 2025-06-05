//19.31.Игра в умножение(4)
//Двое играют в умножение : умножают целое число P на одно из чисел от 2 до 5. Первый игрок всегда начинает с P = 1, делает умножение, затем число умножает второй игрок, снова первый и т.д.Перед началом игры им задают число N, и победителем считается тот, кто первым добьется условия P ≥ N.Определить, кто выиграет при заданном N, если оба играют наилучшим образом.
//Ограничения : 2 ≤ N ≤10000, время 1 с.
//Ввод из файла INPUT.TXT.В первой строке находится количество партий M.В следующих M строках задаются значения N для каждой партии.
//Вывод в файл OUTPUT.TXT.Выводится М строк с числами 1 – если победит первый игрок, или 2 - если победит второй.
//Пример
//Ввод
//1
//17
//Вывод
//1
//
//Дмитриев Данил ПС-21


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("INPUT1.TXT");
    ofstream fout("OUTPUT.TXT");

    int M;
    if (!(fin >> M)) return 0;  
    vector<int> Ns(M);
    for (int i = 0; i < M; i++) {
        fin >> Ns[i]; 
    }

    vector<int> win;
    for (int idx = 0; idx < M; idx++) {
        int N = Ns[idx];
        win.assign(N + 1, 0); 
        for (int p = N; p >= 1; p--) {
            if (p >= N) {
                win[p] = 1;
            }
            else {
                bool canWin = false;
                for (int x = 2; x <= 5; x++) {
                    long long next = static_cast<long long>(p) * x;
                    if (next >= N) {    
                        canWin = true;
                        break;
                    }
                    if (win[next] == 2) {
                        canWin = true;
                        break;
                    }
                }
                win[p] = canWin ? 1 : 2;
            }
        }
        fout << win[1];
        if (idx + 1 < M) fout << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}

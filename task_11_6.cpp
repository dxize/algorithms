//11.6.Длина линии(6)
//Имеется круг радиуса R с центром в начале координат.Заданы две точки(X1, Y1) и(X2, Y2).Требуется найти минимальную длину линии, соединяющей эти точки, но не пересекающей внутренность круга.
//Ввод из файла INPUT.TXT.В первой строке находится целое число N – количество блоков входных данных.Далее следуют N строк, каждая из которых содержит пять вещественных чисел через пробел – X1, Y1, X2, Y2 и R.
//Вывод в файл OUTPUT.TXT.Для каждого блока входных данных выводится одно вещественное число с тремя знаками после запятой - минимальная длина линии.
//Пример
//Ввод
//2
//1 1 - 1 - 1 1
//1 1 - 1 1 1
//Вывод
//3.571
//2.000
//
//Дмитриев Данил ПС-21

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm> 

using namespace std;
using ld = long double;

inline ld sqr(ld x) { return x * x; }

ld dist_point_segment(ld x1, ld y1, ld x2, ld y2) {
    ld dx = x2 - x1, dy = y2 - y1;
    ld len2 = dx * dx + dy * dy;
    if (len2 == 0) return sqrtl(sqr(x1) + sqr(y1)); 

    ld t = -(x1 * dx + y1 * dy) / len2;
    t = max(min(t, 1.0L), 0.0L); 

    ld px = x1 + t * dx, py = y1 + t * dy;
    return sqrtl(sqr(px) + sqr(py));
}

int main() {
    ifstream fin("input5.txt");
    ofstream fout("output_11_6.txt");
    fin.tie(nullptr); fout << fixed << setprecision(3);

    int N; fin >> N;
    while (N--) {
        ld x1, y1, x2, y2, R;
        fin >> x1 >> y1 >> x2 >> y2 >> R;

        ld min_dist = dist_point_segment(x1, y1, x2, y2);
        if (min_dist >= R) {
            fout << sqrtl(sqr(x2 - x1) + sqr(y2 - y1)) << '\n';
            continue;
        }

        ld d1 = sqrtl(sqr(x1) + sqr(y1));
        ld d2 = sqrtl(sqr(x2) + sqr(y2));

        if (d1 == 0 || d2 == 0) {
            fout << (d1 + d2) << '\n';
            continue;
        }

        ld dot = x1 * x2 + y1 * y2;
        ld cos_theta = dot / (d1 * d2);
        cos_theta = max(min(cos_theta, 1.0L), -1.0L); 
        ld beta = acosl(cos_theta);

        ld cos_alpha1 = R / d1;
        cos_alpha1 = max(min(cos_alpha1, 1.0L), -1.0L); 
        ld alpha1 = (d1 >= R) ? acosl(cos_alpha1) : 0;

        ld cos_alpha2 = R / d2;
        cos_alpha2 = max(min(cos_alpha2, 1.0L), -1.0L);
        ld alpha2 = (d2 >= R) ? acosl(cos_alpha2) : 0;

        ld delta = beta - alpha1 - alpha2;
        delta = max(delta, 0.0L);

        ld t1 = (d1 >= R) ? sqrtl(sqr(d1) - sqr(R)) : 0;
        ld t2 = (d2 >= R) ? sqrtl(sqr(d2) - sqr(R)) : 0;

        fout << t1 + t2 + R * delta << '\n';
    }
}
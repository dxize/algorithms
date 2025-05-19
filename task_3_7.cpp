//3.7.Робот 2 (6).
//Робот находится в точке плоскости с целыми координатами(X, Y) (0 ≤ X, Y ≤ 20, X + Y > 0).Он должен достичь цели, находящейся в начале координат.Ход заключается в продвижении на единицу по горизонтали(налево, направо) или вертикали(вверх, вниз).Если робот достигает цели, то немедленно останавливается.Найти количество способов достижения цели ровно за Z шагов(1 ≤ Z ≤ 20).
//Ввод.В единственной строке находятся через пробел X, Y и Z.
//Вывод.В единственной строке вывести количество способов достижения цели.
//Примеры
//Ввод 1      Ввод 2
//1 0 1       0 1 3
//Вывод 1     Вывод 2
//1           5
//Пояснение.Во втором примере возможны следующие варианты движения робота :
//(0, 1) –(0, 2) –(0, 1) –(0, 0);
//(0, 1) –(1, 1) –(0, 1) –(0, 0);
//(0, 1) –(1, 1) –(1, 0) –(0, 0);
//(0, 1) –(-1, 1) –(0, 1) –(0, 0);
//(0, 1) –(-1, 1) –(-1, 0) –(0, 0).
//
//Дмитриев Данил ПС-21

#include <iostream>
#include <vector>

int main() {
    int startX, startY, totalSteps;
    std::cin >> startX >> startY >> totalSteps;

    if (startX + startY > totalSteps || (totalSteps - startX - startY) % 2 != 0) 
    {
        std::cout << "Nope" << std::endl;
        return 0;
    }

    const int offset = 20;
    const int size = 41; 
    std::vector<std::vector<std::vector<long long>>> ways(totalSteps + 1,
        std::vector<std::vector<long long>>(size, std::vector<long long>(size, 0))
    );
    ways[0][startX + offset][startY + offset] = 1;

    for (int step = 1; step <= totalSteps; ++step) 
    {
        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                int realI = i - offset;
                int realJ = j - offset;
                if (realI == 0 && realJ == 0 && step != totalSteps) 
                {
                    ways[step][i][j] = 0;
                    continue;
                }
                long long optionCount = 0;
                if (i > 0)
                {
                    optionCount += ways[step - 1][i - 1][j];    // влево
                }
                if (i < size - 1)
                {
                    optionCount += ways[step - 1][i + 1][j]; // вправо
                }
                if (j > 0)
                {
                    optionCount += ways[step - 1][i][j - 1];    // вниз
                }
                if (j < size - 1)
                {
                    optionCount += ways[step - 1][i][j + 1]; // вверх
                }
                ways[step][i][j] = optionCount;
            }
        }
    }

    std::cout << ways[totalSteps][0 + offset][0 + offset] << std::endl;
    return 0;
}
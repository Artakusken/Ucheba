#include <iostream>
#include "functions.hpp"

void input_array(unsigned short n, int arr[]) {
    std::cout << "Enter " << n << " numbers" << "\n";
    for (unsigned short i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

int main() {
//     8 ВАРИАНТ. ЯКИМОВ АРТЁМ. 6 ПОДГРУППА 3 ГРУППА ПМИ
//     ДЗ 9 "Функции"
// Дана целочисленная матрица {Aij}i=1...n;j=1..n , n<=100.
// Если суммы цифр минимального и максимального элементов матрицы отличаются не более, чем на 2,
// упорядочить столбцы матрицы по неубыванию суммы элементов.

    unsigned short n, m;
    int matrix[N_Max][N_Max];

    ya::ReadMatrix(matrix, n, m);

    int max = ya::FindMaximumInStaticMatrix(matrix, n, m); // 29 45
    int min = ya::FindMinimumInStaticMatrix(matrix, n, m); // 51 15
    std::cout << "max num " << max << ", min num " << min << std::endl;

    if ( (ya::NumberDigitsSum(max) - ya::NumberDigitsSum(min)) < 3) {
        std::cout << "diff is " << ya::NumberDigitsSum(max) - ya::NumberDigitsSum(min) << std::endl;
        for (unsigned short i = 0; i < m - 1; i++) {
            for (unsigned short j = i + 1; j < m; j++) {
                if (ya::MatrixColumnSum(matrix, n, m, i) > ya::MatrixColumnSum(matrix, n, m, j)) {
                    ya::SwapMatrixColumns(matrix, n, m, i, j);
                }
            }
        }
    }
    std::cout << "result" << std::endl;
    ya::WriteMatrix(matrix, n, m);
    return 0;
}

// Я протестил:
// Квадратные 2 порядка
// 29 45 -→ 45 29
// 51 15 -→ 15 51
// Квадратные 3 порядка
// 29 45 44 -→ 45 44 29
// 51 15 25 -→ 15 25 51
// 19 18 17 -→ 18 17 19
// Прямоугольные 5х3
// 29 45 44 -→ 29 44 45
// 51 19 25 -→ 51 25 19
// 19 18 17 -→ 19 17 18
// 19 90 22 -→ 19 22 90
// 44 55 55 -→ 44 55 55
// Прямоугольные 3х5
// 29 45 44 100 8 -→ 8 45 44 29 100
// 51 19 25 101 2 -→ 2 19 25 51 101
// 19 18 17 102 1 -→ 1 18 17 19 102
// Прямоугольные 2х5 с отриц
// -15 4 68 88 91 -→ 68 4 -15 91 88
// 87 65 -80 -8 -19 -→ -80 65 87 -19 -8
// 1х5
// 10 1 20 15 -1 -→ -1 1 10 15 20
// 5х1
// 1 -→ 1
// 2 -→ 2
// 3 -→ 3
// 4 -→ 4
// 10 -→ 10
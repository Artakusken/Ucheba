#include <iostream>
#include <vector>

void PrintVector(std::vector<int> v, unsigned short start = 0, unsigned short end = 0) {
    if (!end) {
        end = v.size();
    }
    std::cout << "vector: ";
    for (unsigned short i = start; i != end; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

size_t FindMaximumInVector(std::vector<int> v, unsigned short d) {
    int max = 1;
    size_t index = 0;

    for (size_t i = d; i != v.size(); ++i) {
        int el = v[i];
        if (el > max) { max = el, index = i; }
    }
    return index;
}


int SortVector(std::vector<int> &v) {
    unsigned short sorted_elems = 0;

    for (size_t i = 0; i != v.size(); ++i) {
        size_t index = FindMaximumInVector(v, sorted_elems);
        int el = v[index];
        int e = v[i];
        v[i] = el;
        v[index] = e;
        sorted_elems++;
    }
    return 0;
}

void dz_seven_pt1(std::vector<int> &arr) {
    unsigned short same_count = 0;
    std::cout << "HW #7" << std::endl;
    std::cout << "Task 1" << std::endl;

    for (int el : arr) {
        char prev_num = el % 10;
        char cur_num;
        el /= 10;

        while (el) {
            cur_num = el % 10;
            if (cur_num == prev_num) { el /= 10; prev_num = cur_num; }
            else break;
        }
        if (not el) { same_count++; }
        if (same_count == 3) { break; }
    }

    if (same_count >= 3) {
        std::cout << same_count << std::endl;
        SortVector(arr);
    }
    else { std::cout << same_count << std::endl; }

}

int dz_seven_pt3(){
    unsigned short n, m;
    std::cout << "HW #7" << std::endl;
    std::cout << "Task 3" << std::endl;

    std::cout << "Enter matrix dimension \n";
    std::cin >> n;
    std::cin >> m;

    if (n < 1 or n > 100 or m < 1 or m > 100) {
        std::cout << "N and M must be in range [1, 100]";
        return -1;
    }

    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
    std::cout << "Enter matrix" << "\n";
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != m; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int max = 0;
    unsigned short col = 0;
    for (size_t j = 0; j < m; j++) {
        int mul = 1;
        for (size_t i = 0; i < n; i++) {
            mul *= matrix[i][j];
        }
        std::cout << mul << " ";
        if (mul > max) {max = mul, col = j;}
    }
    std::cout << "\n";

    std::cout << "Final matrix:\n";
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != m; ++j) {
            if (j == col) {matrix[i][j] = matrix[i][j] - 3;}
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Biggest multiplication in column: " << ++col << "\n";
    return 0;
}

int main() {
//     8 ВАРИАНТ. ЯКИМОВ АРТЁМ. 3 ГРУППА 6 ПОДГРУППА ПМИ
//     ДЗ 11 "Указатели" но задание просто говорит использовать динамические массивы (я использовал только вектор)

//     Дана последовательность натуральных чисел {aj}j=1...n (n<=10000).
//     Если в последовательности есть не менее 3-х чисел, все цифры которых одинаковы, упорядочить последовательность по невозрастанию.
//	std::vector<int> arr = {103, 2432, 75, 444, 6666, 18, 40, 54};  // только 2 числа с одинаковыми цифрами
	std::vector<int> arr = {103, 2432, 75, 444, 6666, 18, 40, 5};  // 3 числа (6666, 444, 5)
    PrintVector(arr);
    dz_seven_pt1(arr);
    PrintVector(arr);

    std::cout << "\n";
//     Дана целочисленная матрица {Aij}i=1..n,j=1..m (n,m<=100). *Введите её
//     Найти столбец с наибольшим произведением элементов и уменьшить все элементы этого столбца на 3.
    dz_seven_pt3();

    return 0;
}
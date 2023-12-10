#include "functions.hpp"
#include <iostream>

namespace ya
{
    unsigned short NumberDigitsSum(int num) {
        short sum = 0;
        num = abs(num);
        while (num) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    void PrintStaticArray(int arr[], unsigned short n) {
        std::cout << "Array of length " << n << ": ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }

    bool SameDigitsInNumber(int num) {
        char digits[10]{};

        while (num) {
            digits[num % 10] += 1;
            num /= 10;
        }

        for (char digit : digits) {
            if (digit > 1) {return true;}
        }
        return false;
    }

    int FindMaximumInStaticArray(int arr[], unsigned short n, bool return_value) {
        int max = INT_MIN;
        unsigned short index = 0;

        for (int i = 0; i < n; i++) {
            int el = arr[i];
            if (el > max) { max = el, index = i; }
        }

        if (return_value) { return max; }
        return index;
    }

    int FindMinimumInStaticArray(int arr[], unsigned short n, bool return_value) {
        int min = INT_MAX;
        unsigned short index = 0;

        for (int i = 0; i < n; i++) {
            int el = arr[i];
            if (el < min) { min = el, index = i; }
        }

        if (return_value) { return min; }
        return index;
    }

    void ReadMatrix(int matrix[N_Max][N_Max], unsigned short& n, unsigned short& m)
    {
        std::cin >> n >> m;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                std::cin >> matrix[i][j];
    }

    void WriteMatrix(int matrix[N_Max][N_Max], unsigned short n, unsigned short m)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    int FindMaximumInStaticMatrix(int matrix[N_Max][N_Max], unsigned short n, unsigned short m) {
        int max = INT_MIN;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int el = matrix[i][j];
                if (el > max) { max = el; }
            }
        }
        return max;
    }

    int FindMinimumInStaticMatrix(int matrix[N_Max][N_Max], unsigned short n, unsigned short m) {
        int min = INT_MAX;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int el = matrix[i][j];
                if (el < min) { min = el; }
            }
        }
        return min;
    }

    int MatrixColumnSum(int matrix[N_Max][N_Max], unsigned short n, unsigned short m, unsigned short column_index) {
        int sum = 0;

        for (int j = 0; j < n; j++) {
            sum += matrix[j][column_index];
        }
        return sum;
    }

    void SwapMatrixColumns(int matrix[N_Max][N_Max], unsigned short n, unsigned short m, unsigned short LColumn, unsigned short RColumn) {
        int temp_column[n];

        for (unsigned short i = 0; i < n; i++) {
            temp_column[i] = matrix[i][LColumn];
            matrix[i][LColumn] = matrix[i][RColumn];
        }
        for (unsigned short i = 0; i < n; i++) {
            matrix[i][RColumn] = temp_column[i];
        }
    }
}
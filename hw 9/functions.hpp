#pragma once
#define N_Max 100

namespace ya
{
    unsigned short NumberDigitsSum(int num);

    void PrintStaticArray(int arr[], unsigned short n);

    bool SameDigitsInNumber(int num);

    int FindMaximumInStaticArray(int arr[], unsigned short n, bool return_value = false);

    int FindMinimumInStaticArray(int arr[], unsigned short n, bool return_value = false);

    void ReadMatrix(int matrix[N_Max][N_Max], unsigned short& n, unsigned short& m);

    void WriteMatrix(int matrix[N_Max][N_Max], unsigned short n, unsigned short m);

    int FindMaximumInStaticMatrix(int matrix[N_Max][N_Max], unsigned short n, unsigned short m);

    int FindMinimumInStaticMatrix(int matrix[N_Max][N_Max], unsigned short n, unsigned short m);

    int MatrixColumnSum(int matrix[N_Max][N_Max], unsigned short n, unsigned short m, unsigned short column_index);

    void SwapMatrixColumns(int matrix[N_Max][N_Max], unsigned short n, unsigned short m, unsigned short LColumn, unsigned short RColumn);
}

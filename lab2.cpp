// Вариант 1

#include <iostream>
#include <ctime>

const int N = 7;
const int M = 10;

int main()
{
    // Выделяем память под матрицу
    int** matrix = new int*[N];
    for (int i = 0; i < N; i++)
        matrix[i] = new int[M];

    // Генерируем матрицу
    srand(static_cast<unsigned int>(time(NULL)));           // Устанавливаем seed
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrix[i][j] = rand() % 2;

    // Выводим матрицу
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cout.width(3);                             // Устанавливаем ширину между элементами в строке
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }

    // Формируем массив
    int* vector = new int[M];
    for (int j = 0; j < M; j++)
    {
        vector[j] = 0;
        int i = 0;
        while (i < N)
        {
            if (matrix[i][j] == 1)
            {
                vector[j] = 1;
                i = N;
            }
            else
                i++;
        }
    }

    // Выводим массив
    std::cout << std::endl;
    for (int j = 0; j < M; j++)
    {
        std::cout.width(3);                                 // Устанавливаем ширину между элементами в строке
        std::cout << vector[j];
    }

    // Освобождаем память
    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] vector;
}

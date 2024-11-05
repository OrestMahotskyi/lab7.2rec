#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1);
}

void CreateRows(int** a, const int N, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, N, Low, High, 0);
    if (rowNo < N - 1)
        CreateRows(a, N, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int N, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int N, int rowNo) {
    PrintRow(a, rowNo, N, 0);
    if (rowNo < N - 1)
        PrintRows(a, N, rowNo + 1);
    else
        cout << endl;
}

int FindMinInColumn(int** a, int rows, int col, int i = 0, int minVal = 1000) {
    if (i == rows) return minVal;
    if (a[i][col] < minVal) minVal = a[i][col];
    return FindMinInColumn(a, rows, col, i + 1, minVal);
}

int FindMaxInColumn(int** a, int rows, int col, int i = 0, int maxVal = -1000) {
    if (i == rows) return maxVal;
    if (a[i][col] > maxVal) maxVal = a[i][col];
    return FindMaxInColumn(a, rows, col, i + 1, maxVal);
}

void findIndices(int** a, int rows, int j, int minVal, int maxVal, int& minRow, int& maxRow, int i = 0) {
    if (i >= rows) return; // Вихід з рекурсії
    if (a[i][j] == minVal) minRow = i; // Знаходження рядка з мінімальним значенням
    if (a[i][j - 1] == maxVal) maxRow = i; // Знаходження рядка з максимальним значенням
    findIndices(a, rows, j, minVal, maxVal, minRow, maxRow, i + 1);
}

void SwapMinWithMax(int** a, int rows, int cols, int j = 1) {
    if (j >= cols) return; // Вихід з рекурсії, якщо стовпці закінчилися

    int minVal = FindMinInColumn(a, rows, j); // Мінімальний у парному стовпці
    int maxVal = FindMaxInColumn(a, rows, j - 1); // Максимальний у непарному стовпці

    int minRow = -1, maxRow = -1;
    findIndices(a, rows, j, minVal, maxVal, minRow, maxRow); // Виклик функції для пошуку індексів

    if (minRow != -1 && maxRow != -1) {
        swap(a[minRow][j], a[maxRow][j - 1]); // Виконання обміну
    }

    SwapMinWithMax(a, rows, cols, j + 2); // Рекурсивний виклик для наступного парного стовпця
}

int main() {
    srand((unsigned)time(NULL));
    int N;
    cout << "N = "; cin >> N;
    cout << endl;

    int** a = new int*[N];
    for (int i = 0; i < N; i++)
        a[i] = new int[N];

    int Low = -9, High = 9;
    CreateRows(a, N, Low, High, 0);
    PrintRows(a, N, 0);

    SwapMinWithMax(a, N, N);
    cout << "Modified matrix:" << endl;
    PrintRows(a, N, 0);

    for (int i = 0; i < N; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
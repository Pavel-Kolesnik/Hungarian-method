#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

int SearchSum(int arr[6][6]) {
    int sum = 0;
    const int m = 6;
    const int n = 6;
    int a[m][n] = { {8, 12,  4,  9, 10,  6},
                   {7,  5, 15,  3,  6,  4},
                   {9,  4,  6, 12,  7, 10},
                   {5,  3,  2,  6,  4,  5},
                   {3,  8,  6,  5,  4,  3},
                   {4,  7,  4,  9, 10,  2} };
    //Отбор нулей
    int arrsum[6][6];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) arrsum[i][j] = arr[i][j];
    }
    for (int j = 0; j < n; j++) {
        int k = 0;
        for (int i = 0; i < m; i++) {
            if (arrsum[i][j] == 0) k = k + 1;
            if ((k >= 2) && (arrsum[i][j] == 0)) arrsum[i][j] = -1;
        }
    }
    //Проверка на продолжение Венгерского метода
    for (int i = 0; i < m; i++) {
        int k = 0;
        for (int j = 0; j < n; j++) if (arrsum[i][j] == 0) k = k + 1;
        if (k > 1) {
            sum = -1;
            break;
        }
    };
    for (int i = 0; i < m; i++) {
        int k = 0;
        for (int j = 0; j < n; j++) if (arrsum[i][j] != 0) k = k + 1;
        if (k == m) {
            sum = -1;
            break;
        }
    };
    int num = 0;
    if (sum != -1) {
        for (int i = 0; i < m; i++) {
            int k = 0;
            num = num + 1;
            for (int j = 0; j < n; j++) {
                if (arrsum[i][j] == 0) k = k + 1;
                if ((arrsum[i][j] == 0) && (k == 1)) {
                    sum = sum + a[i][j];
                    cout << "Salary " << num << " employee: " << a[i][j] << endl;
                }
            }
        }
        cout << "Sum = " << sum << endl;
    }
    return sum;
}

int main()
{
    const int m = 6;
    const int n = 6;
    int a[m][n] = { {8, 12,  4,  9, 10,  6},
                   {7,  5, 15,  3,  6,  4},
                   {9,  4,  6, 12,  7, 10},
                   {5,  3,  2,  6,  4,  5},
                   {3,  8,  6,  5,  4,  3},
                   {4,  7,  4,  9, 10,  2} };
    //Начальная матрица
    cout << "Start matrix:" << endl;
    int arr1[6][6];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            arr1[i][j] = a[i][j];
            cout.width(2);
            cout << arr1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    //Венгерский метод
    for (int i = 0; i < m; i++) {
        int min = arr1[i][0];
        for (int j = 0; j < n; j++) if (arr1[i][j] < min) min = arr1[i][j];
        for (int j = 0; j < n; j++) arr1[i][j] -= min;
    }

    for (int j = 0; j < n; j++) {
        int min = arr1[0][j];
        for (int i = 0; i < m; i++) if (arr1[i][j] < min) min = arr1[i][j];
        for (int i = 0; i < m; i++) arr1[i][j] -= min;
    }
    //Результат Венгерского метода
    cout << "Result Venger metod:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout.width(2);
            cout << arr1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    //Нахождение суммы
    cout << "Search Sum:" << endl;
    SearchSum(arr1);
    cout << endl;
    //Продолжение Венгерского метода
    cout << "Continue Venger metod:" << endl;
    while (SearchSum(arr1) == -1) {
        int arr2[6][6];
        for (int i = 0; i < m; i++) {
            int k = 0;
            int arr_s[7];
            for (int j = 0; j < n; j++) if (arr1[i][j] == 0) k = k + 1;
            for (int j = 0; j < n; j++) {
                arr2[i][j] = arr1[i][j];
                if (k > 1 && k <= n) {
                    arr_s[j] = -1;
                    arr2[i][j] = arr_s[j];
                }
            }
        }
        for (int j = 0; j < n; j++) {
            int k = 0;
            int arr_k[6];
            for (int i = 0; i < m; i++) if (arr1[i][j] == 0) k = k + 1;
            for (int i = 0; i < m; i++) {
                if (k > 1 && k <= n) {
                    arr_k[i] = -1;
                    arr2[i][j] = arr_k[i];
                }
            }
        }
        for (int i = 0; i < m; i++) {
            int k = 0;
            int arr_s[6];
            for (int j = 0; j < n; j++) if (arr2[i][j] == 0) k = k + 1;
            for (int j = 0; j < n; j++) {
                if (k == 1) {
                    arr_s[j] = -1;
                    arr2[i][j] = arr_s[j];
                }
            }
        }
        int min = a[0][0];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) if (arr2[i][j] != -1 && arr2[i][j] < min) min = arr2[i][j];
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) if (arr2[i][j] != -1) arr2[i][j] -= min;
        }
        //Нахождение элементов на пересечении вычеркнутых строк и столбцов
        int n_s[6];
        for (int i = 0; i < m; i++) {
            int k = 0;
            for (int j = 0; j < n; j++) if (arr2[i][j] == -1) k = k + 1;
            n_s[i] = k;
        }
        int m1[6] = { 0 };
        for (int i = 0; i < m; i++) if (n_s[i] == 6) m1[i] = i;

        int n_k[6];
        for (int j = 0; j < n; j++) {
            int k = 0;
            for (int i = 0; i < m; i++) if (arr2[i][j] == -1) k = k + 1;
            n_k[j] = k;
        }
        int m2[6] = { 0 };
        for (int i = 0; i < m; i++) if (n_k[i] == 6) m2[i] = i;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((arr2[i][j] == arr2[m1[i]][m2[j]]) && (m1[i] != 0) && (m2[j] != 0)) arr2[i][j] -= 1;
            }
        }
        //Передача результатов матрицы arr2 в матрицу arr1
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (arr2[i][j] == -2) arr1[i][j] += min;
                if ((arr1[i][j] == (arr2[i][j] == 0)) || (arr1[i][j] == (arr2[i][j] + min))) arr1[i][j] = arr2[i][j];
                if (arr1[i][j] == -1) arr1[i][j] = 0;
            }
        }
        cout << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout.width(2);
                cout << arr1[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        //Нахождение суммы
        cout << "Search Sum:" << endl;
        SearchSum(arr1);
    }
}

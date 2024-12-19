#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 65365


void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// Функция для сортировки простой вставкой

void insertionSort(int *arr, int n) {
    int i, el, j;
    for (i = 1; i < n; i++) {
        printf("Начало работы алгоритама для %d шага:\n", i);
        printf("Элемент подлежащий сортировке - %d\n", arr[i]);

        el = arr[i]; // элемент подлежащий сортировке
        j = i - 1; // последн эл списка


        // Перемещаем элементы arr[0..i-1], которые больше key, на одну позицию вперед
        while (j >= 0) {
            printf("Сравниваем %d и %d: ", arr[j], el);
            if (arr[j] > el) {
                printf("%d > %d -- сдвигаем %d\n", arr[j], el, arr[j]);
                arr[j + 1] = arr[j];

                // вывод массива
                printf("Результат сдвига: ");
                for (int k = 0; k < n; k++) {
                    printf("%d ", arr[k]);
                    if (k == (i-1)) {
                        printf("| ");
                    }
                }
                printf("\n");
            } else {
                printf("%d <= %d -- %d на своем месте\n", arr[j], el, arr[j]);

                printf("\n");
                break;
            }
            j = j - 1;
        }

        arr[j + 1] = el;


        // вывод массива
        printf("Результат %d шага: ", i);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
            if (k == i && k != n-1) {
                printf("| ");
            }
        }
        printf("\n\n");
    }
}


void selectionSort(int *arr, int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        printf("Начало работы алгоритама для %d шага:\n", i);

        // поиск индекса минимального элемента в неотсортированной части
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        printf("Минимальный элемент в неотсортированной части - %d\n", arr[minIndex]);


        if (minIndex != i) {
            printf("Меняем местами элементы %d и %d\n", arr[i], arr[minIndex]);
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }

        // Выводим массив после текущей итерации
        printf("Результат %d шага: ", i+1);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
            if (k == i && k != n-1) {
                printf("| ");
            }
        }
        printf("\n\n");
    }
}


int main() {
    // setlocale(LC_ALL, "Rus");

    // Ввод длины массива
    int n;
    printf("Введите размер массива: ");
    scanf("%d", &n);

    // Проверка корректности длины
    if (n <= 0) {
        printf("Размер массива должен быть положительным числом.\n");
        return 1; // Завершаем программу с ошибкой
    }

    // Выделяем память для массива
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    // Запрашиваем у пользователя элементы массива
    printf("Введите элементы массива:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Исходный массив: \n");
    printArray(arr, n);


    int ch;
    printf("Выберите сортировку\n1. Сортировка простой вставкой\n2. Сортировка выбором\nВведите номер: ");
    scanf("%d", &ch);
    printf("\n\n");
    switch (ch) {
        case 1:
            insertionSort(arr, n);
            break;
        case 2:
            selectionSort(arr, n);
            break;
        default:
            printf("Неверный выбор");
            return 1;
    }


    printf("Список после сортировки: ");
    printArray(arr, n);
    free(arr);
    return 0;
}
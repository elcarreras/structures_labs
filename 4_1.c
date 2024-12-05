#include <locale.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    char data;
    struct Node* next;
} Node;


// Создание узла
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));    // Выделение памяти
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Добавление элемента в начало
void pushFront(Node** head, int data) {
    Node* newNode = createNode(data);       // Создаем новый элемент
    newNode->next = *head;                  // Добавляем в него адрес след эл-та
    *head = newNode;                        // Изменяем хранящийся адрес на указатель начала списка
}

// Добавление элемента в конец
void pushBack(Node** head, char data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {                    // Случай когда нода пуста (пуста полностью)
        *head = newNode;                    // Мы добавляем новую ноду
        return;
    } else {                                // Иначе мы идем до конца списка и добавляем эл-т
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;

    }
}

// Удаление элемента в начале
void popFront(Node** head) {
    if (*head == NULL) {                       // Если список пуст
        printf("The list is empty\n");
        return;
    }
    Node* temp = *head;                        // Иначе копируем адрес первого эл-та
    *head = (*head)->next;                     // Заменяем адрес первого эл-та в переменной которая хранит адрес первого эл-та
    free(temp);                        // Очищаем первый элемент в памяти
}

// Удаление элемента в конце
void popBack(Node** head) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Добавление эл-та в списке по индексу
void insertAt(Node** head, int index, int data) {
    if (index < 0) {
        printf("Индекс не может быть отрицательным\n");
        return;
    }
    if (index == 0) {
        pushFront(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;

    for (int i = 0; i < index - 1; i++) {
        if (temp == NULL || temp->next == NULL) {
            printf("Индекс выходит за пределы списка\n");
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Удаление элемента в середине списка по индексу
Node* deleteAt(Node** head, Node* target) {
    if (*head == NULL || target == NULL) {
        printf("Невозможно удалить элемент: список пуст или указатель неверен.\n");
        return NULL;
    }

    if (*head == target) { // Если удаляемый узел - первый в списке
        *head = target->next; // Новый head указывает на следующий узел
        free(target);         // Удаляем текущий узел
        return *head;         // Возвращаем новый head
    }

    Node* temp = *head;
    while (temp->next != NULL && temp->next != target) {
        temp = temp->next;
    }

    if (temp->next == target) {
        temp->next = target->next; // Пропускаем удаляемый узел
        free(target);              // Очищаем память
        return temp->next;         // Возвращаем следующий узел
    }

    printf("Узел не найден в списке.\n");
    return NULL;
}
// Печать всех элементов списка
void printList(Node* head) {
    while (head != NULL) {
        printf("%c", head->data);
        head = head->next;
    }
    // printf(" -> NULL\n");
}

// Освобождение памяти, занятой списком
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


// Функции для меню
void actionPrintList(Node*, Node*);


// 1 Начало работы  B
void actionStartWork(int* isStarted) {
    if (*isStarted) {
        printf("Работа со списком уже начата.\n");
    } else {
        *isStarted = 1;
        printf("Работа со списком начата.\n");
    }
}

// 2 Сделать список пустым  B
void actionMakeEmpty(Node** head, Node** current) {
    freeList(*head);        // Очищение памяти
    *head = NULL;
    *current = NULL;
    printf("Список очищен.\n");
}

// 3 Проверка на пустоту списка  B
void actionCheckEmpty(Node** head, Node** current) {
    if (*head == NULL) {
        printf("Список пуст.\n");
    } else {
        printf("Список не пуст.");
        actionPrintList(*head, *current);
    }
}

// 4 Установление рабочего указателя на начало  B
void actionSetToStart(Node* head, Node** current) {
    if (head == NULL) {
        printf("Список пуст.\n");
        *current = head;
    } else {
        *current = head;
        printf("Рабочий указатель установлен на начало списка.\n");
    }
}

// 5 Проверка в конце ли рабочий указатель  В
void actionCheckAtEnd(Node* current) {
    if (current == NULL) {
        printf("Рабочий указатель не установлен.\n");
    } else if (current != NULL && current->next == NULL) {
        printf("Рабочий указатель в конце списка.\n");
    } else {
        printf("Рабочий указатель не в конце списка.\n");
    }
}

// 6 Передвинуть рабочий указатель вперед  B
void actionMoveForward(Node** current) {
    if (*current == NULL) {
        printf("Рабочий указатель не установлен.\n");
    } else if (*current != NULL && (*current)->next == NULL) {
        printf("За рабочим указателем нет элемента.\n");
    } else {
        *current = (*current)->next;
        printf("Рабочий указатель передвинут вперед.\n");
    }
}

// 7 Вывести элемент за рабочим указателем  В
void actionShowNext(Node* current) {
    if (current == NULL) {
        printf("Рабочий указатель не установлен.\n");
    } else if (current != NULL && current->next == NULL) {
        printf("За рабочим указателем нет элемента.\n");
    } else {
        printf("Значение элемента за указателем: %c\n", current->next->data);
    }
}

// 8 Удаление за рабочим указателем  В
void actionDeleteNext(Node** head, Node** current) {
    if (*current == NULL) {
        printf("Рабочий указатель не установлен.\n");
    } else if (*current != NULL && (*current)->next == NULL) {
        printf("За рабочим указателем нет элемента.\n");
    } else {
        Node * target = (*current)->next;
        (*current)->next = deleteAt(head, target);
        printf("Элемент за рабочим указателем удален.\n");
    }
}

// 9 Взять элемент списка за рабочим указателем  В
void actionGetNextElement(Node** current, Node** head, char* outData) {
    if (*current == NULL) {
        printf("Рабочий указатель не установлен.\n");
    } else if (*current != NULL && (*current)->next == NULL) {
        printf("За рабочим указателем нет элемента.\n");
    } else {
        *outData = (*current)->next->data;
        Node * target = (*current)->next;
        (*current)->next = deleteAt(current, target);
        printf("Элемент за рабочим указателем сохранен.\n");
    }
}

// 10 Изменения элемента за рабочим указателем  В
void actionModifyAfterCurrent(Node* current) {
    if (current == NULL) {
        printf("Рабочий указатель не установлен.\n");
    } else if (current != NULL && current->next == NULL) {
        printf("За рабочим указателем нет элемента\n");
    } else {
        char data;
        printf("Введите новое значение: ");
        scanf(" %c", &data);
        current->next->data = data;
        printf("Значение элемента изменено.\n");
    }
}

// 11 Добавить элемент после указателя  В
void actionAddAfterCurrent(Node** head, Node** current) {
    if (*head == NULL) {
        char data;
        printf("Введите значение нового элемента: ");
        scanf(" %c", &data);
        *head = createNode(data);
        *current = *head;
    } else {
        char data;
        printf("Введите значение нового элемента: ");
        scanf(" %c", &data);
        Node* newNode = createNode(data);
        newNode->next = (*current)->next;
        (*current)->next = newNode;
        printf("Элемент добавлен за рабочим указателем, конец списка.\n");
    }
}

// 12 Вывести список  В
void actionPrintList(Node* head, Node* current) {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    } else {
        printf("Список: ");
        Node* temp = head;
        while (temp != NULL) {
            if (temp == current) {
                printf("\033[31m%c\033[0m", temp->data); // Выделяем текущий элемент
            } else {
                printf("%c", temp->data);
            }
            temp = temp->next;
        }
        printf("\n");
    }
}

// 13 Завершение работы со списком  B
void actionEndWork(Node** head, Node** current, int* isStarted) {
    freeList(*head);
    *head = NULL;
    *current = NULL;
    *isStarted = 0;
    printf("Работа со списком завершена.\n");
}

// 14 Очистка списка и выход  B
void actionExitProgram(Node** head) {
    freeList(*head);
    printf("Программа завершена.\n");
}


int main(void) {
    Node* head = NULL;        // Указатель на начало
    Node* current = NULL;     // Рабочий указатель
    int isStarted = 0;        // Флаг, проверяющий, начата ли работа со списком
    int choice;


    while (1) {
        printf("\nМеню:\n");
        printf("1.  Начать работу со списком\n");
        printf("2.  Сделать список пустым\n");
        printf("3.  Проверка: список пустой или не пустой?\n");
        printf("4.  Установить рабочий указатель в начало списка\n");
        printf("5.  Проверка: рабочий указатель в конце списка?\n");
        printf("6.  Передвинуть рабочий указатель вперед\n");
        printf("7.  Показать значение элемента списка за указателем\n");
        printf("8.  Удалить элемент списка за рабочим указателем\n");
        printf("9.  Взять элемент списка за рабочим указателем\n");
        printf("10. Изменить значение элемента списка за рабочим указателем\n");
        printf("11. Добавить элемент за рабочим указателем\n");
        printf("12. Распечатать структуру данных\n");
        printf("13. Закончить работу со списком\n");
        printf("14. Закончить работу программы\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        // Проверка на то какое выбрано действие и начата ли работа
        if (choice <= 0 || choice > 14) {
            printf("Некорректная операция, выберите операцию от 1 до 14");
            continue;
        } else if (choice != 1 && !isStarted && choice != 14) {
            printf("Сначала начните работу со списком (выберите 1).\n");
            continue;
        }

        switch (choice) {
            case 1:
                actionStartWork(&isStarted);
                actionPrintList(head, current);
                break;
            case 2:
                actionMakeEmpty(&head, &current);
                actionPrintList(head, current);
                break;
            case 3:
                actionCheckEmpty(&head, &current);
                break;
            case 4:
                if (head == NULL) {
                    printf("Список пуст.\n");
                    continue;
                } else {
                    current = head;
                    printf("Рабочий указатель установлен на начало списка.\n");
                    actionPrintList(head, current);
                }
                break;
            case 5:
                actionCheckAtEnd(current);
                actionPrintList(head, current);
                break;
            case 6:
                actionMoveForward(&current);
                actionPrintList(head, current);
                break;
            case 7:
                actionShowNext(current);
                actionPrintList(head, current);
                break;
            case 8:
                actionDeleteNext(&head, &current);
                actionPrintList(head, current);
                break;
            case 9: {
                char nextData = '\0';
                actionGetNextElement(&current, &head, &nextData);
                if (nextData != '\0') {
                    printf("Элемент за указателем: %c\n", nextData);
                }
                actionPrintList(head, current);
                break;
            }
            case 10:
                actionModifyAfterCurrent(current);
                actionPrintList(head, current);
                break;
            case 11:
                actionAddAfterCurrent(&head, &current);
                actionPrintList(head, current);
                break;
            case 12:
                actionPrintList(head, current);
                break;
            case 13:
                actionEndWork(&head, &current, &isStarted);
                break;
            case 14:
                actionExitProgram(&head);
                return 0;
            default: printf("Неверный выбор, попробуйте снова.\n"); break;
        }
    }
    return 0;
}
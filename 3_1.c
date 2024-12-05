/* 
 * Дана строка, группы символов разделенные пробелами
 * (1 или несколькими) и не содержащими пробелов внутри
 * себя назовем словами. Найти длину самого короткого слова
*/
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
// comment this on win
// VVVV
# define INT_MAX INT32_MAX

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


// Добавление элемента в середину


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

// Добавление элемента в середине списка по индексу
void deleteAt(Node** head, int index) {
    if (*head == NULL) {
        printf("Список пуст\n");
        return;
    }
    if (index < 0) {
        printf("Индекс не может быть отрицательным\n");
        return;
    }
    if (index == 0) {
        popFront(head);
        return;
    }
    Node* temp = *head;
    Node* prev = NULL;

    for (int i = 0; i < index; i++) {
        if (temp == NULL || temp->next == NULL) {
            printf("Индекс выходит за пределы списка\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    free(temp);
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





int main(void) {
    setlocale(0, "Russian");
    Node* list = NULL;
    int len = 0;
    char f;

    printf("Введите текст: ");
    for (int i = 0; (f = getchar()) != '\n'; i++) {
        pushBack(&list, f);
        len += 1;
    }

    if (list == NULL) {
        printf("Spisok pust!");
        return 1;
    }

    Node* temp = list;
    int word_len = 0, min_len = INT_MAX;
    for (int i = 0; i < len; i++) {
        if (temp->data != ' ') {
            word_len++;
        }
        else if (word_len > 0) {
            // Если встретили пробел и до этого было слово, проверяем его длину
            if (word_len < min_len) {
                min_len = word_len;
            }
            word_len = 0;
        }

        if (temp->next != NULL) {
            temp = temp->next;
        }
    }

    // Проверка последнего слова, если строка не оканчивается пробелом
    if (word_len > 0 && word_len < min_len) {
        min_len = word_len;
    }
    printf("Dlina samogo korotkogo slova: %d\n", min_len);


    // Задача на удаление добавление в центр списка
    temp = list;
    word_len = 0, min_len = INT_MAX;
    int min_word_index = 0;
    int curr_word_index = 0;
    for (int i = 0; i < len; i++) {
        if ((temp->data != ' ')) {
            word_len++;
        }
        else if (word_len > 0) {
            // Если встретили пробел и до этого было слово, проверяем его длину
            if (word_len < min_len) {
                min_word_index = curr_word_index;
                curr_word_index = (i + 1);
                min_len = word_len;
            } else if (temp->next != NULL) {
                curr_word_index = (i + 1);
            }
            word_len = 0;
        }

        if (temp->next != NULL) {
            temp = temp->next;
        } else {
            if (word_len < min_len) {
                min_word_index = curr_word_index;
                min_len = word_len;
            }
        }
    }

    printf("\nBefore: ");
    printList(list); // list before edit

    for (int i = 0; i < min_len; i++) {
        deleteAt(&list, min_word_index);
    }
    insertAt(&list, min_word_index, '$');
    printf("\nAfter:  ");
    printList(list);



    freeList(list);
    return 0;
}
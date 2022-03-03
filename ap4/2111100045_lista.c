#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct tDate
{
    int day;
    int month;
    int year;
};
typedef struct tDate date;

struct tStudent
{
    char registration[10];
    char name[40];
    date birthday;
    float average;
    struct tStudent *next;
    struct tStudent *prev;
};
typedef struct tStudent student;

struct tListController
{
    student *first;
    student *last;
};
typedef struct tListController listController;

void freeMemory(listController list)
{
    student *aux;
    aux = list.first;
    while (aux != NULL)
    {
        list.first = aux->next;
        free(aux);
        printf("*");
        aux = list.first;
    }
    printf("\n\n");
}

date setDate(int d, int m, int y)
{
    date birthday;
    birthday.day = d;
    birthday.month = m;
    birthday.year = y;
    return birthday;
}

listController insertStudent(listController list)
{
    int d, m, y;
    student *s, new, *aux;
    char prev_registration[10];
    s = (student *)malloc(sizeof(student));
    scanf(" %s", prev_registration);
    scanf(" %s", new.registration);
    scanf(" %s", new.name);
    scanf(" %d/%d/%d", &d, &m, &y);
    scanf(" %f", &new.average);

    new.birthday = setDate(d, m, y);
    *s = new;

    if (list.first == NULL)
    {
        s->next = NULL;
        s->prev = NULL;
        list.first = s;
        list.last = s;
        return list;
    }

    for (aux = list.first; aux != NULL; aux = aux->next)
    {
        if (strcmp(aux->registration, prev_registration) == 0)
        {
            if(aux->next != NULL){
                aux->next->prev = s;
            }
            else{
                list.last = s;
            }
            
            s->next = aux->next;
            s->prev = aux;
            aux->next = s;
            
            return list;
        }
    }
   
    list.first->prev = s;
    s->next = list.first;
    s->prev = NULL;
    list.first = s;
    
    return list;
}

listController deleteStudent(listController list)
{
    char registration[10];
    scanf(" %s", registration);
    student *auxnext;
    student *aux = list.first;
    if (list.first == NULL)
    {
        printf("Lista Vazia!\n");
        return list;
    }

    while (aux != NULL)
    {
        if (strcmp(aux->registration, registration) == 0)
        {
            if (aux == list.first)
            {
                list.first = aux->next;
                list.first->prev = NULL;
            }
            else if (aux == list.last)
            {
                list.last = aux->prev;
                list.last->next = NULL;
            }
            else
            {
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
            }
            auxnext=aux->next;
            free(aux);
            aux = auxnext;
        }
        else{
        aux=aux->next;
        }
    }
    return list;
}

void printStudents(listController list)
{
    student *aux;
    if (list.first == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }
    for (aux = list.first; aux != NULL; aux = aux->next)
    {
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->registration, aux->name, aux->birthday.day, aux->birthday.month, aux->birthday.year, aux->average);
    }
}

void printStudentsReverse(listController list)
{
    student *aux;
    if (list.first == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }
    for (aux = list.last; aux != NULL; aux = aux->prev)
    {
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->registration, aux->name, aux->birthday.day, aux->birthday.month, aux->birthday.year, aux->average);
    }
}

void countElements(student *first)
{
   
    student *aux;
    int count = 0;
    for (aux = first; aux != NULL; aux = aux->next)
    {
        count++;
    }
    printf("%d\n", count);
}

listController init_list()
{
    listController list;
    list.first = NULL;
    list.last = NULL;
    return list;
}

int main()
{
    listController list = init_list();

    int op;

    scanf("%d", &op);
    do
    {
        switch (op)
        {
        case 1:
            list = insertStudent(list);
            break;

        case 2:
            list = deleteStudent(list);
            break;
        case 3:
            printStudents(list);
            break;
        case 4:
            printStudentsReverse(list);
            break;
        case 5:
            countElements(list.first);
            break;

        case 0:
            break;
        }

        scanf("%d", &op);
    } while (op != 0);
    freeMemory(list);
    return 0;
}
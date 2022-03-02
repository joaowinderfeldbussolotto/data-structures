#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
};
typedef struct tStudent student;

void freeMemory(student *s)
{
    student *aux;
    aux = s;
    while (aux != NULL)
    {
        s = aux->next;
        free(aux);
        printf("-");
        aux = s;
    }
    printf("\n\n");
}

date setDate(int d, int m, int y){
    date birthday;
    birthday.day = d;
    birthday.month = m;
    birthday.year = y;
    return birthday;

}


student *insertStudent(student *first)
{

    char name[40];
    float average;
    int d, m, y;
    char registration[10];
    student *s;
    s = (student*)malloc(sizeof(student));
    student *aux = first;
    scanf(" %s", registration);
    scanf(" %s", name);
    scanf("%d/%d/%d", &d, &m, &y);
    scanf("%f", &average);

    date birthday = setDate(d,m,y);
    s->average = average;
    strcpy(s->name, name);
    strcpy(s->registration, registration);
    s->birthday = birthday;
    s->next = NULL;

    if (first == NULL)
        return s;

    for (; aux != NULL; aux = aux->next)
    {
        if (aux->next == NULL)
        {
            aux->next = s;
            return first;
        }
    }

    return first;
}
student *deleteStudent(student *first)
{
    char registration[10];
    scanf(" %s", registration);

    student *aux = first;
    student *prev = first;
    if (first == NULL)
    {
        printf("Lista Vazia!\n");
        return first;
    }
    
    while(aux != NULL){
        if (strcmp(aux->registration, registration) == 0){
            if (aux == first){
                first = aux ->next;
                free(aux);
                prev = first;
                aux = prev;
            }
            else{
                prev->next = aux->next;
                free(aux);
                aux = prev->next;
            }
        }
        else{
        prev = aux;
        aux = aux->next;
        }
        
    }
    return first;
}

void printStudents(student *first)
{
    student *aux = first;
    if (first == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }
    for (; aux != NULL; aux = aux->next)
    {
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->registration, aux->name, aux->birthday.day, aux->birthday.month, aux->birthday.year, aux->average);
    }
}

void printStudentsReverse(student *f)
{
    if (f == NULL)
    {
        return;
    }
    
        printStudentsReverse(f->next);
        printf("%s, %s, %d/%d/%d, %.2f\n", f->registration, f->name, f->birthday.day, f->birthday.month, f->birthday.year, f->average);
    
}

void countElements(student *first){
    if (first == NULL){
        printf("Lista Vazia!\n");
        return;
    }
    student* aux;
    int count = 0;
    for(aux= first;aux != NULL; aux = aux->next){
        count++;
    }
    printf("%d\n", count);
}


int main()
{   
    student *first = NULL;
    int op;
    scanf("%d", &op);
    do
    {
        switch (op)
        {
        case 1:
            first = insertStudent(first);
            break;
        case 2:
            first = deleteStudent(first);
            break;
        case 3:
            printStudents(first);
            break;
        case 4:
        if(first == NULL){
            printf("Lista Vazia!\n");
        }
            printStudentsReverse(first);
            break;
        case 5:
            countElements(first);
            break;
        case 0:
            break;
        }

        scanf("%d", &op);
    } while (op != 0);
    freeMemory(first);
    return 0;
}
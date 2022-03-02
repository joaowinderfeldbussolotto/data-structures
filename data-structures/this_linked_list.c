#include <stdio.h>
#include <stdlib.h>

struct spoint
{
    int x, y;
    struct spoint *next;
};
typedef struct spoint tpoint;




void freeMemory(tpoint *p)
{
    tpoint *aux;
    aux = p;
    while (aux != NULL)
    {
        p = aux->next;
        free(aux);
        aux = p;
    }
}

void printPoints(tpoint *p)
{
    tpoint *aux = p;
    if (aux == NULL)
        printf("Lista vazia!\n");
    for (; aux != NULL; aux = aux->next)
        printf("(%d,%d)\n", aux->x, aux->y);
}

void printPointsInv(tpoint *p)
{
    if (p == NULL)
        return;
    printPointsInv(p->next);
    printf("(%d,%d)\n", p->x, p->y);
}

tpoint *getLast(tpoint *f)
{
    tpoint *aux = f;
    if (aux == NULL)
        return NULL;
    for (; aux->next != NULL; aux = aux->next)
        ;
    return aux;
}

tpoint *setPoint(tpoint *first, int x, int y)
{
    //tpoint *pt, *aux = getLast(f);
    tpoint *pt, *aux = first;
    pt = (tpoint*)malloc(sizeof(tpoint));
    pt->x = x;
    pt->y = y;
    pt->next = NULL;
    if (first == NULL){
        return pt;
    }
    for(;aux!=NULL;aux=aux->next){
        if (aux->next == NULL){
            aux->next = pt;
        }
    }
    return first;
}


int main()
{
    tpoint *first = NULL;


    int i = 1;

    while (i < 10)
    {
        first = setPoint(first,i * 10, i * 10 + 1);
        i++;
    }
    printPoints(first);
    printPointsInv(first);
    freeMemory(first);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>

struct sQueue{
    char c;
    struct sQueue *next;
};
typedef struct sQueue queueElem;

struct sSentinel {
    queueElem *first;
    queueElem *last;
};typedef struct sSentinel sentinel;


sentinel init_queue(){
    sentinel s;
    s.first = NULL;
    s.last = NULL;
    return s;
}

int isEmpty(sentinel queue){
    if (queue.first == NULL){
        return 1;
    }
    return 0;
}

sentinel insert_element(sentinel queue){
    char c;
    scanf(" %c", &c);
    queueElem *elem = (queueElem*) malloc(sizeof(queueElem));
    elem -> c = c;
    elem-> next = NULL;
    if (isEmpty(queue)){
        queue.first = elem;
        queue.last = elem;
        return queue;
    }

    queue.last->next = elem;
    queue.last = elem;
    return queue;
}

sentinel delete_element(sentinel queue){

    queueElem *aux = queue.first;
    if (queue.first == queue.last){
        queue = init_queue();
        return queue;
    }

    queue.first = aux->next;
    free(aux);
    return queue;
}

void free_queue(sentinel queue){
    queueElem *aux = queue.first;

    while(queue.first !=NULL){
        aux = queue.first;
        printf("%c\n", aux->c);
        queue = delete_element(queue);
        
    }
    queue.last = NULL;
}
void print_queue(sentinel queue){
    queueElem *aux = queue.first;
    while(aux!=NULL){
        printf("%c\n",aux->c);
        aux = aux->next;
    }
}

int main(){
    sentinel queue;
    queue = init_queue();
    int i;
    for (i = 0; i < 5; i++){
        queue = insert_element(queue);
    }
    printf("\n");
    free_queue(queue);

    

    return 0;
}

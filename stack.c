#include <stdlib.h>
#include <stdio.h>


struct sStackElem {
    char elem;
    struct sStackElem *next;
};

typedef struct sStackElem stackElem;

struct sController {
    stackElem *top;
};
typedef struct sController stack;

stack init_stack(){
    stack s;
    s.top = NULL;
    return s;
}

int isEmpty(stack s) {
 return (s.top == NULL);
}

stack push(stack s, char c)
{
    stackElem *new = (stackElem*) malloc(sizeof(stackElem));
    new->elem = c;
    new->next = s.top;


    if(s.top == NULL){
        s.top = new;
        return s;
    }

    new -> next = s.top;
    s.top = new;
    return s;
}

stack popElem(stack s){
    stackElem *aux = s.top;
    if (!isEmpty(s)){
        s.top = aux->next;
        free(aux);
        return s;
    }
}

stack releaseMem(stack s){
    while(s.top != NULL){
        printf("%c\n", s.top->elem);
        s = popElem(s);
    }

}

void printStack(stack s){
    stackElem *aux = s.top;
    while(aux!=NULL){
        printf("%c\n", aux->elem);
        aux = aux->next;
    }
}
int main(){

    stack s = init_stack();
    int i;
    char c;
    for(i = 0; i < 5; i++){
        scanf(" %c", &c);
        s = push(s,c);
    }
    //printStack(s);
    printf("Apagando:\n");
    releaseMem(s);
    
    return 0;
}

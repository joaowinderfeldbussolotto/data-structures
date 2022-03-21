#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct sStackElem {
    char url[100];
    struct sStackElem *next;
};

typedef struct sStackElem StackElem;

struct sController {
    StackElem *top;
};
typedef struct sController Stack;

Stack init_stack(){
    Stack s;
    s.top = NULL;
    return s;
}

int isEmpty(Stack s) {
 return (s.top == NULL);
}




Stack push(Stack urls, char url[])
{
    StackElem *new = (StackElem*) malloc(sizeof(StackElem));
    strcpy(new->url, url);

    new->next = urls.top;
    urls.top = new;
    return urls;
}

Stack popElem(Stack urls){
    StackElem *aux = urls.top;
    if (isEmpty(urls)){
        printf("Vazio\n");
        return urls;
    }

    
    printf("%s\n", aux->url);
    urls.top = aux->next;
    free(aux);
    return urls;
    
    
}

void releaseMem(Stack urls){
    if(isEmpty(urls)){
        printf("!");

    }
    while(!isEmpty(urls)){
        printf("@");
        StackElem *aux = urls.top;
        urls.top = aux->next;
        free(aux);
    }
    printf("\n");

}

void printStack(Stack s){
    StackElem *aux = s.top;
    while(aux!=NULL){
        printf("%s\n", aux->url);
        aux = aux->next;
    }
}


Stack menu(Stack urls){
    char url[100];
    scanf(" %s", url);

    if(!strcmp(url, "B")){
        urls = popElem(urls);
    }
    else if(!strcmp(url, "E")){

        releaseMem(urls);
    }
    else{

        urls = push(urls, url);

        //printStack(urls);
    }
    
    return urls;

}


int main(){

    Stack urls = init_stack();
    int flag = 1;
    while(1){
        char url[100];
        scanf(" %s", url);

        if(!strcmp(url, "B")){
            urls = popElem(urls);
        }
        else if(!strcmp(url, "E")){
            releaseMem(urls);
            break;
        }
        else{
            urls = push(urls, url);
        }
    }
    
    return 0;
}

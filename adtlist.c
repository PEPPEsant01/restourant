#include "adtlist.h"

#include <stdio.h> 
#include <stdlib.h>



// utilita di movimento di base della lista
// creare una nuova lista
list newlist(item item){
    // creo una lista di un elemento senza valore
    list list = calloc(1, sizeof(struct node));
    if (NULL == list) {
        return NULL;
    }
    // carico il valore dell'elemento, e imposto il valore precedente e successivo a null
    list->item = item;
    list->next = NULL;
    list->prev = NULL;
    // carico il numero 1 come grandezza della lista
    list->size = calloc(1, sizeof(int));
    if (NULL == list->size) {
        free(list);
        return NULL;
    }
    *list->size = 1;

    // restituisco la lista correttamente creata
    return list;
}

// ritorna un elemento in posizione precedente nella lista
list prevelement(list list){
    return list->prev;
}

// ritorna un elemento in posizione successiva nella lista
list nextelement(list list){
    return list->next;
}

// ritorna il primo elemento nella lista
list headlist(list list){
    if (NULL == list) {
        return NULL;
    }
    while(NULL != list->prev){
        list = prevelement(list);
    }
    return list;
}

// ritorna l'ultimo elemento nella lista
list taillist(list list){
    if (NULL == list) {
        return NULL;
    }
    while(NULL != list->next){
        list = nextelement(list);
    }
    return list;
}







// utilita di gestione della lista
// riconta gli elementi presenti in una lista
list recount(list list){
    list = taillist(list);
    int *count = calloc(1, sizeof(int));
    if(NULL == count) {
        return NULL;
    }
    *count = 0;
    while(NULL != list){
        free(list->size);
        list->size = count;
        (*count)++;
        if(NULL == prevelement(list)){
            return list;
        }
        list = prevelement(list);
        
    }
    return list;
}

// concatena 2 liste
list catlist(list list1, list list2){
    if (NULL == list1) {
        return headlist(list2);
    }
    if (NULL == list1) {
        return headlist(list2);
    }
    list1 = taillist(list1);
    list2 = headlist(list2);

    list1->next = list2;
    list2->prev = list1;
    
    return recount(list1);
}

// ritorna il valore della grandezza della lista
int listsize(list list){
    if (NULL == list) {
        return 0;
    }
    return *(list->size);
}

// ritorna l'elemento in posizione pos nella lista
list movelist(list list, int pos){
    if (NULL == list) {
        return NULL;
    }
    if (0 > pos || pos >= listsize(list)) {
        return NULL;
    }
    int i = 0;
    while(i < pos){
        list = nextelement(list);
        i++;
    }
    return list;
}

//cancella un elemento della lista nella posizione corrente
list deletethis(list list){
    if (NULL == list) {
        return NULL;
    }
    struct node *prev;
    prev = prevelement(list);
    struct node *next;
    next = nextelement(list);

    
    
    list->size -= 1;
    if (0 == list->size) {
        free(list->size);
    };
    clearitem(list->item);
    free(list);
    if (NULL != prev) {
        prev->next = next;
    };
    if (NULL != next) {
        next->prev = prev;
        return headlist(next);
    };
    return headlist(prev);
}

// cancella un elemento della lista in posizione pos
list deleteitem(list list, int pos){
    if (NULL == list) {
        return NULL;
    }
    if (0 > pos || pos >= listsize(list)) {
        return NULL;
    };
    list = movelist(list, pos);
    
    return deletethis(list);
}



// cancella tutti gli elementi della lista
void clearlist(list list){
    if (NULL == list) {
        return;
    }
    list = taillist(list);
    list = prevelement(list);
    while(NULL != list){
        list = deletethis(list->next);
        if(NULL != list->prev){
            list = prevelement(list);
        } else {
            list = deletethis(list);
        }
    }
    return;
}







// utilita di ricerca nella lista
// cerca la posizione di un elemento
int searchpos(item item, list list){
    
    int i = 0;
    list = headlist(list);
    while (NULL != list){
        if (list->item == item){
            return i;
        }

        list = nextelement(list);
        i++;

    }
    return -1;

}

// restituise l'elemento nella posizione di ricerca
list searchitem(item item, list list){
    return movelist(list, searchpos(item, list));
}

// estrae l'elemento nella posizione corrente
item extractthis(list list){
    if(NULL == list){
        return NULL;
    }
    return list->item;
}

// estrae l'elemento nella posizione indicata
item extractitem(list list, int pos){
    return extractthis(movelist(list, pos));
}







// utilita avanzate lista
// aggiungi un elemento nella posizione corrente
list additem(item item,list list, int pos){
    if (NULL == list) {
        return NULL;
    }
    if (0 > pos || pos > listsize(list)) {
        return NULL;
    };
    struct node *prev;
    struct node *next;
    if (listsize(list) == pos){
        list = taillist(list);
        prev = list;
        next = NULL;
    } else {
        list = movelist(list, pos);
        prev = prevelement(list);
        next = list;
    }
    struct node *addlist;
    addlist = newlist(item);
    if(NULL == addlist){
        return NULL;
    }
    addlist->next = next;
    addlist->prev = prev;
    if (NULL != prev) {
        prev->next = addlist;
    };
    if (NULL != next) {
        next->prev = addlist;
    };
    list->size += 1;
    return headlist(addlist);


    
}

// ricarica il valore di un elemento, nella posizione corrente
list reloaditem(item item, list list){
    if (NULL == list) {
        return NULL;
    }
    free(list->item);
    list->item = item;
    return list;
}

// copia una lista dalla posizione in cui si trova, funzione interna
list internalcopylist(list list){

    if (NULL == list) {
        return NULL;
    }
    struct node *copylist;
    copylist = newlist(extractthis(list));
    while(NULL!= nextelement(list)){
        list = nextelement(list);
        copylist->next = newlist(copyitem(extractthis(list)));
        copylist = nextelement(copylist);
        if(NULL == copylist){
            return NULL;
        }
        copylist->prev = prevelement(copylist);    

    }
    copylist->next = NULL;
    return recount(copylist);
    
}

// copia una lista per intero, usando la libreria interna
list copylist(list list){
    return internalcopylist(headlist(list));
}

// copia una lista a partire dalla posizione successiva
list upplist(list list){
    return internalcopylist(nextelement(list));
}
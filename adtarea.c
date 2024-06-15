#include <stdio.h>
#include <stdlib.h>
#include "adtarea.h"



// lista di supporto per il ristorante
// funzione interna per la creazione di una lista
area newinternalarea(table actual, list menu, int *size){
    area area = calloc(1, sizeof(struct section));
    area->next = NULL;
    area->menu = menu;
    area->actual = actual;
    area->size = size;
    return area;
}

// funzione esposta per la creazione di una area
area newArea(table actual, list menu){
    int *size = calloc(1, sizeof(int));
    *size = 1;
    struct section *area = newinternalarea(actual, menu, size);
    return area;
}

// funzione interna per ottenere l'ultimo elemento della area
area tailArea(area area){
    while(area->next!= NULL){
        area = area->next;
    }
    return area;
}

// funzione esposta per aggiungere un nuovo tavolo alla area
void addArea(area area, table actual){
    area = tailArea(area);
    area->next = newinternalarea(actual, area->menu, area->size);
    area->size += 1;
    return;
}

// funzione esposta per ottenere il tavolo numero id
table gettable(area area, int id){
    while(area->next!= NULL){
        if(getnumber(area->actual) == id){
            return area->actual;
        }
    }
    return NULL;
}

// stampa gli id dei tavoli presenti
void printarea(area area){
    fprintf(stdout,"Tavoli presenti:\n");
    int i = 0;
    while(area!= NULL){
        fprintf(stdout,"tavolo numero: %d\n in posizione: %d\n\n", getnumber(area->actual), i );
        area = area->next;
        i++;
    }
    return;
}

// funzione interna per eliminare un tavolo dalla area
area internaldeletetable(area area){
    struct section *temp = area->next;
    cleartable(area->actual);
    free(area);
    area = temp;
    area->size -= 1;
    return area;
}

// funzione esposta per eliminare un tavolo dalla area
area deletetable(area area, int pos){
    if(pos == 0){
        return internaldeletetable(area);
    }
    int i;
    struct section *temp = area;
    for(i = 1; i < pos - 1; i++){
        area = area->next;
    }
    area = internaldeletetable(area->next);
    return area;
}

// funzione esposta per cancellare l'area
void cleararea(area area){
    while(area->next!= NULL){
        struct section *temp = area->next;
        internaldeletetable(area);
        area->next = temp;
    }
    return;
}

// funzione esposta per ottenere il numero di tavoli della area
int areasize(area area){
    return *(area->size);
}

// esporto il menu da visionare
list getmenu(area area){
    return area->menu;
}



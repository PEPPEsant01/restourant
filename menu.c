#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"



// utilita per il menu
// nuovo menu con lettura intelligente dell'input
list newmenu(FILE *fp){
    
    int quantity = 0;
    char *name = calloc(666,sizeof(char));
    float price = 0.0;
    int date = 0;
    int shipped = 2;
    list menu;
    int i=0;
    if(NULL == fp || stdin == fp){
        while(1 > quantity){
            fprintf(stdout, "quanti piatti vuoi inserire?\ninserire un numero n >= 1\n");
            fscanf(stdin, "%d", &quantity);
        }
        fprintf(stdout, "inserisci il nome del piatto numero: 0\n");
        fscanf(stdin, "%s", &name);
        do {
            fprintf(stdout, "inserisci il prezzo di un piatto\nil prezzo non puo essere negativo\n");
            fscanf(stdin, "%f", &price);
        } while (0 >= price);
        menu = newlist(newitem(name,price,date,shipped));
        
        if(1 < quantity) {
            for(i = 1; i < quantity; i++) {
                fprintf(stdout, "inserisci il nome del piatto numero: %d\n", i);
                fscanf(stdin, "%s", &name);
                do {
                    fprintf(stdout, "inserisci il prezzo di un piatto\nil prezzo non puo essere negativo\n");
                    fscanf(stdin, "%f", &price);
                } while (0 >= price);
                menu = additem(newitem(name,price,date,shipped),menu,listsize(menu));
            }
        
        }
        return menu;
    }
    fscanf(fp, "%d", &quantity);
    fscanf(fp, "%s", &name);
    fscanf(fp, "%f", &price);
    menu = newlist(newitem(name,price,date,shipped));
    if(1 < quantity) {
        for(int i = 1; i < quantity; i++) {
            fscanf(fp, "%s", &name);
            fscanf(fp, "%f", &price);
            menu = additem(newitem(name,price,date,shipped),menu,listsize(menu));
        }
        
    }
    return menu;
}

// stampa l'elemento singolo
void printitem(item item, int order){
    fprintf(stdout, "piatto: %s\n", getname(item));
    fprintf(stdout, "prezzo: %f\n", getprice(item));
    if(1 == order){
        fprintf(stdout, "in data: %d\n", getdate(item));
        fprintf(stdout, "arrivato: %d\n", getshipped(item));
    }
    fprintf(stdout, "\n\n");
}

// stampa la lista
void printlist(list list, int order){
    if(NULL == list){
        return;
    }
    item item;
    list = headlist(list);
    for(int i=0; i<listsize(list); i++){
        item = extractthis(list);
        fprintf(stdout, "stampo l'elemento numero: %d\n", i);
        printitem(item, order);

    }
    return;
}


// utilita per i tavoli
//seleziona i piatti da portare al tavolo in base alle preferenze dell'utente
list selectlist(list list, FILE *fp){
    if (NULL == list){
        return NULL;
    }
    struct node *actual;
    struct node *cat;
    int pos = 0;
    if(NULL == fp || stdin == fp){
        printlist(list, 0);
        while(1){
            fprintf(stdout, "quale elemento vuoi inserire? \nscrivi -1 per uscire\n sono accettati i valori da -1 a %d", listsize(list) - 1);
            fscanf(stdin, "%d", &pos);
            if(0 <= pos && pos < listsize(list)){
                cat = newlist(orderitem(extractitem(list, pos)));
                actual = catlist(actual, cat);
            } else if(-1 == pos){
                break;
            }
        }
        
    } else {
        while(1){
            
            fscanf(fp, "%d", &pos);
            if(0 <= pos && pos < listsize(list)){
                cat = newlist(orderitem(extractitem(list, pos)));
                actual = catlist(actual, cat);
            } else if(-1 == pos){
                break;
            }
        }
    }

    return actual;
}

// crea un nuovo tavolo
table newtable(list list, FILE *fp){
    table table = malloc(sizeof(struct order));
    if(NULL == table){
        return NULL;
    }
    int numbered = 0;
    if(NULL == fp || stdin == fp){
        do {
            fprintf(stdout, "inserisci il numero del tavolo(intero positivo):\n");
            fscanf(stdin, "%d", &numbered);
        } while (0 > numbered);
    } else {
        fscanf(fp, "%d", &numbered);
    }
    
    
    table->number = numbered;
    table->orders = selectlist(list, fp);
    return table;
}   

// cancella il tavolo
void cleartable(table table){
    if(NULL == table){
        return;
    }
    clearlist(table->orders);
    free(table);
    return;
}

// aggiungi altri ordini
table addorder(table table, list list, FILE *fp){
    if(NULL == table){
        return NULL;
    }
    if(NULL == list){
        return NULL;
    }
    
    table->orders = catlist(table->orders, selectlist(list, fp));
    return table;
}

// trova il numero del tavolo
int getnumber(table table){
    if(NULL == table){
        return 0;
    }
    return table->number;
}


// utilita piatti 
// stampa gli ordini
void printorder(table table){
    if(NULL == table){
        return;
    }
    printlist(table->orders, 1);
    return;
}

// contrassegna un ordine arrivato
table markorder(table table, int pos){
    if(NULL == table){
        return NULL;
    }
    if(0 > pos || pos >= listsize(table->orders)){
        return NULL;
    }
    setshipped(extractitem(table->orders, pos));
    return table;
}

// stampa gli ordini arrivati
void printshipped(table table){
    if(NULL == table){
        return;
    }
    int quantity = 0;
    item item;
    for(int i=0; i<listsize(table->orders); i++){
        table->orders = movelist(table->orders, i);
        item = extractthis(table->orders);
        if(1 == getshipped(item)){
            fprintf(stdout, "stampo l'elemento numero: %d\n", quantity);
            quantity += 1;
            printitem(item, 1);
        }
        
    }
    return;
    
}

// stampa gli ordini in attesa
void printunshipped(table table){
    if(NULL == table){
        return;
    }
    int quantity = 0;
    item item;
    for(int i=0; i<listsize(table->orders); i++){
        table->orders = movelist(table->orders, i);
        item = extractthis(table->orders);
        if(0 == getshipped(item)){
            fprintf(stdout, "stampo l'elemento numero: %d\n", quantity);
            quantity += 1;
            printitem(item, 1);
        }
        
    }
    return;
    
}

// cancella gli ordini arrivati
void tablerefresh(table table){
    if(NULL == table){
        return;
    }
    int quantity = 0;
    item item;
    for(int i=0; i<listsize(table->orders); i++){
        table->orders = movelist(table->orders, i);
        item = extractthis(table->orders);
        if(0 == getshipped(item)){
            deletethis(table->orders);
            i -= 1;
        }
        
    }
    return;
}

// restituisci il numero di piatti
int tableordersize(table table){
    return listsize(table->orders);
}






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "adtlist.h"

data databuilder(int order){

    data newItem;

    char buffer[100];
    int ingredientCount;

    fprintf(stdout, "Inserisci il nome: ");
    fscanf(stdin, "%s", buffer);
    newItem.name = strdup(buffer);

    fprintf(stdout, "Inserisci il prezzo: ");
    fscanf(stdin, "%f", &newItem.price);

    fprintf(stdout, "Quanti ingredienti? ");
    fscanf(stdin, "%d", &ingredientCount);

    /*newItem.ingredients = calloc(ingredientCount + 1 , sizeof(char *));
    for (int i = 0; i <= ingredientCount; i++) {
        if (ingredientCount == i){
            newItem.ingredients[i] == NULL;
            break;
        }
        fprintf(stdout, "Inserisci l'ingrediente %d: ", i + 1);
        fscanf(stdin, "%s", buffer);
        newItem.ingredients[i] = strdup(buffer);
    }*/

    if (0 == order) {
        newItem.date = 0;
        newItem.shipped = 2;
    } else {
        // Imposta la data corrente
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        newItem.date = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
        newItem.shipped = 0;
    }

    return newItem;

}

data *dataloader(int order, FILE *fp){
    if (NULL == fp){
        return NULL;
    }

    data *newItem = (data*)malloc(sizeof(data)); // Allocate on the heap
    if (newItem == NULL) {
        return NULL; // Handle memory allocation error
    }

    char buffer[100];
    int ingredientCount;

    fscanf(fp, "%s", buffer);
    newItem->name = strdup(buffer);

    fscanf(fp, "%f", &newItem.price);

    /*fscanf(fp, "%d", &ingredientCount);
    newItem.ingredients = malloc(ingredientCount * sizeof(char *));
    for (int i = 0; i < ingredientCount; i++) {
        fscanf(fp, "%s", buffer);
        newItem.ingredients[i] = strdup(buffer);
    }*/

    if (1 == order) {
        newItem->date = 0;
        newItem->shipped = 2;
    } else {
        // Imposta la data corrente
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        newItem->date = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
        newItem->shipped = 0;
    }

    return newItem;

}

data dataupdate(data item){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    item.date = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
    item.shipped = 0;

    return item;
}

list *dataselect(list *list, FILE *fp) {
    if (NULL == list) {
        return NULL;
    }

    list *selected = NULL; // Lista di ritorno 
    list *cat;
    int posix;
    // Se fp è NULL, leggi dalla tastiera
    if (NULL == fp) {
        // Stampo gli elementi della lista
        printlist(list);
        // Chiedo all'utente quali elementi inserire
        while(1){
            fprintf(stdout, "quale elemento vuoi inserire? \nscrivi -1 per uscire\n sono accettati i valori da -1 a %d", listcount(list) - 1);
            fscanf(stdin, "%d", posix);
            if(0 <= posix || listcount(list) > posix ){
                cat = newlist(dataupdate(extractitem(list, posix)));
                selected = catlist(selected, cat);

            } else if (-1 == posix) {
                break;
            }

        }
        // ... (Implementa la logica per l'inserimento da tastiera) ...
    } else { // Altrimenti leggi dal file
        while(1){

            fscanf(fp, "%d", posix);
            if(0 <= posix || listcount(list) > posix ){
                cat = newlist(dataupdate(extractitem(list, posix)));                
                selected = catlist(selected, cat);
            } else if (-1 == posix) {
                break;
            }

        }
    }

    return selected; // Restituisci la lista di ritorno
}



data *dataarray(int numbered, int order, FILE *fp){

    
    data *datalist = (data*)calloc(numbered, sizeof(data));
    data *dataloader = datalist;

    if (NULL != fp) {
        for (int i = 0; i < numbered; i++) {
            *dataloader = dataloader(order, fp);
            dataloader += 1;
        }
        return datalist;
    }

    for (int i = 0; i < numbered; i++) {
        fprintf(stdout, "Inserimento del piatto numero %d: ", i + 1);
        *dataloader = databuilder(order);
        dataloader++;
    }

    return datalist;

}

list *listmenubuilder(int order){
    int numbered = 0;
    data *datalist;
        //chiedo all'utente quanti dati inserire
    fprintf(stdout, "quanti piatti vuoi inserire?");
    fscanf(stdin, "%d", &numbered);

    datalist = dataarray(numbered,order,NULL);

    return newlistnumbered(datalist,numbered);

}

list *listmenuloader(int order, FILE *fp){
    int numbered = 0;
    data *datalist;
        //chiedo all'utente quanti dati inserire
    fscanf(fp, "%d", &numbered);

    datalist = dataarray(numbered,order,fp);

    return newlistnumbered(datalist,numbered);

}


void printItem(data item) {
    int i = 0;
    fprintf(stdout, "Nome: %s, \nPrezzo: %.2f, \nData: %d, \nSpedito: %d\n\n\n\n", item.name, item.price, item.date, item.shipped);


}

void printlist(list *list){    
    if(NULL == list){
        return;
    }
    list *posil = headlist(list);
    int i = 0;
    while (NULL != posil){
        fprintf(stdout, "\n\nstampo l'elemento numero %d\n", i);
        printItem(extractthis(&posil));
        posil = nextelement(&posil);
        i++;
    }
    return;
}









table *neworderlist(list *list, FILE *fp){
    int tableid = -1;
    table *new_table = (table *)malloc(sizeof(table));
    if (new_table == NULL) {
        return NULL;
    }
    new_table->number = tableid;

    if (!listvalid(list)) {
        free(new_table);
        return NULL;
    }

    data test = extractthis(list);
    if (2 == test.shipped || 0 == test.date)
    {
        free(new_table);
        return NULL;
    }
    
    if (NULL != fp){

        
        fscanf(fp, "%f", tableid);
        new_table->number = tableid;
        new_table->orders = dataselect(list, fp);
        

    }else{
        do {
        fprintf(stdout, "in che tavolo ti ritrovi?");
        fscanf(stdin, "%d", tableid);
        } while (0 <= tableid);

        new_table->number = tableid;

            new_table->orders = dataselect(list, fp);

    
    }
    

    return new_table;
}

int dataequals(data dt1, data dt2){
    if (0 != strcmp(dt1.name, dt2.name)){
        return 0;
    }
    if (dt1.price != dt2.price){
        return 0;
    }
    /*if (dt1.ingridients != dt2.ingridients){
        return 0;
    }*/
    if (dt1.date != dt2.date){
        return 0;
    }
    if (dt1.shipped != dt2.shipped){
        return 0;
    }


    return 1;
}

table* orderarrived(table *table, list *plate) {
    data platedata = extractthis(plate);
    list *posil = headlist(table.orders);
    data search;
    while (NULL != posil){
        posil searchitem(platedata, posil);
        search = extractthis(posil);
        if (1 == dataequals(platedata,search)){
            search.shipped = 1;
            posil = reloaditem(shipped,posil);
            table.orders = headlist(posil);
            return table;
        }
        posil = upplist(posil);

    }


    return NULL;
}

table *arrived(table *table){
    list *posil = table->orders;
    posil = headlist(posil);
    data test;
    while (NULL != posil) {
        test = extractthis(posil);
        if (1 == test.shipped) {
            printf("Ordine arrivato: %s \nTempo di inserimento: %d\n", test.name, test.date);
        }
        posil = nextelement(posil);
    }
    return table;
}

table *tablerefresh(table *table){
list *posil = table->orders;
    posil = headlist(posil);
    data test;
    i = 0;
    
    while (NULL != posil) {
        test = extractthis(posil);
        if (1 == test.shipped) {
            posil = deleteitem(posil, i);
            table->orders = posil;
        }else {
            posil = nextelement(posil);
            i++;
        }
        
    }
    return table;
}

table *waiting(table *table){
    list *posil = table->orders;
    posil = headlist(posil);
    data test;
    while (NULL != posil) {
        test = extractthis(posil);
        if (0 == test.shipped) {
            printf("Ordine arrivato: %s, Tempo di inserimento: %d\n", test.name, test.date);
        }
        posil = nextelement(posil);
    }
    return table;
}

table *orderrefresh(table *table,list *list, FILE *fp){
    if(NULL == table){
        return NULL;
    }

    table->order = catlist(table->order,dataselect(list, fp));
    
    return tablerefresh(table);

}

void printorders(table *table){
    printlist(table.orders);
}

void deletelist(list *list){
    if(NULL == list){
        return;
    }
    list = headlist(list);
    while(NULL != list){
        data exit = extractthis(list);
        free(exit.name);
        list = deleteitem(list,0);
    }

}

void deletetable(table *table){
    deletelist(table->orders);
    free(table);
    return;
}


#include "item.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>


// utilita di base gestione dati
// creo la struttura item
item newitem(char *name, float price, int date, int shipped){
    // creo una oggetto item vuoto;
    item item = calloc(1, sizeof(struct data));
    if (NULL == item){
        return NULL;
    }
    // carico il valore dell'oggetto
    //strcpy(newitem->name,name);
    int i = 0;
    item->name = calloc(strlen(name) + 1, sizeof(char));
    while (name[i] != '\0') {
        item->name[i] = name[i];
        i++;
    }
    item->name[i] = '\0';
    item->price = price;
    item->date = date;
    item->shipped = shipped;
    // restituisco l'oggetto'
    return item;
}

// copio l'oggetto item in una nuova struttura
item copyitem(item item){  
    // creo una copia dell'oggetto
    struct data *newitem = calloc(1, sizeof(struct data));
    if (NULL == newitem){
        return NULL;
    }
    // carico il valore dell'oggetto
    int i = 0;
    newitem->name = calloc(strlen(item->name) + 1, sizeof(char));
    while (item->name[i] != '\0') {
        newitem->name[i] = item->name[i];
        i++;
    }
    newitem->name[i] = '\0';
    //strcpy(newitem->name,item->name);
    newitem->price = item->price;
    newitem->date = item->date;
    newitem->shipped = item->shipped;
    // restituisco l'oggetto'
    return newitem;
}

// confronto 2 oggetti per verificare se sono uguali
int compareitem(item item1, item item2){
    if (0 != strcmp(item1->name, item2->name)){
        return 0;
    }
    if (item1->price != item2->price){
        return 0;
    }
    if (item1->date != item2->date){
        return 0;
    }
    if (item1->shipped != item2->shipped){
        return 0;
    }
    
    return 1;
    
}

// cancella lo spazio in ram dell'oggetto
void clearitem(item item){
    free(item->name);
    free(item);
}







// ottenimento dati dell'oggetto
// restituisco il nome dell'oggetto
char *getname(item item){
    return item->name;
}

// restituisco il prezzo dell'oggetto
float getprice(item item){
    return item->price;
}

// restituisco l'ora di richiesta dell'oggetto
int getdate(item item){
    return item->date;
}

// restituisco il valore shipped dell'oggetto
int getshipped(item item){
    return item->shipped;
}







// aggiornamento dati dell'oggetto
// imposto un oggetto nello stato di arrivato
item setshipped(item item){
    item->shipped = 1;
    return item;
}

// imposta un oggetto nello stato di ordinato
item setorder(item item){
    item->shipped = 0;
    return item;
}

// aggiorno la data di un oggetto
item updatedate(item item){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    item->date =  + tm.tm_mday * 1000000 + tm.tm_hour * 10000 + tm.tm_min * 100 + tm.tm_sec;
    return item;
}







// utilità aggiuntive
// restituisce un ordine pronto per essere ordinato
item orderitem(item item){  
    // creo una copia dell'oggetto
    struct data *newitem = copyitem(item);
    if (NULL == newitem){
        return NULL;
    }
    // restituisco l'oggetto'
    return setorder(updatedate(newitem));
}
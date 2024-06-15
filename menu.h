#include <stdio.h> // Includi la libreria standard per le operazioni di input/output
#include <stdlib.h> // Includi la libreria standard per l'allocazione dinamica della memoria
#include "adtlist.h"

typedef struct order *table;
struct order{
    int number;
    list orders;
    
};

// utilita per il menu
list newmenu(FILE *fp);
void printitem(item item, int order);
void printlist(list list, int order);


// utilita per i tavoli
list selectlist(list list, FILE *fp);
table newtable(list list, FILE *fp);
void cleartable(table table);
table addorder(table table, list list, FILE *fp);
int getnumber(table table);


// utilita piatti 
void printorder(table table);
table markorder(table table, int pos);
void printshipped(table table);
void printunshipped(table table);
void tablerefresh(table table);
int tableordersize(table table);
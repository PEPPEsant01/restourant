#include <stdio.h> // Includi la libreria standard per le operazioni di input/output
#include <stdlib.h> // Includi la libreria standard per l'allocazione dinamica della memoria
#include "adtlist.h"

typedef struct {
    int number;
    list *orders;
    
}table;

list *dataselect(list *list, FILE *fp);
list *listmenubuilder(int order);
list *listmenuloader(int order, FILE *fp);
void printlist(list *list);
table *neworderlist(list *list, FILE *fp);
int dataequals(data dt1, data dt2);
table *orderarrived(table *table, list *plate);
table *arrived(table *table);
table *tablerefresh(table *table);
table *waiting(table *table);
table *orderrefresh(table *table,list *list, FILE *fp);
void printorders(table *table);
void deletetable(table *table);
void deletelist(list *list);
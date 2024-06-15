#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


typedef struct section *area;
struct section {
    area next;
    list menu;
    table actual;
    int *size;
};


// lista di supporto per il ristorante
area newArea(table actual, list menu);
void addArea(area area, table actual);
table gettable(area area, int id);
void printarea(area area);
area deletetable(area area, int pos);
void cleararea(area area);
int areasize(area area);
list getmenu(area area);


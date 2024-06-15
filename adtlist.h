#include <stdio.h>
#include <stdlib.h>
#include "item.h"

#define NULLITEM 0





typedef struct node *list;
struct node {
    list next;
    list prev;
    item item;
    int *size;
};

// utilita di movimento di base della lista
list newlist(item item);
list prevelement(list list);
list nextelement(list list);
list headlist(list list);
list taillist(list list);

// utilita di gestione della lista
list catlist(list list1, list list2);
int listsize(list list);
list movelist(list list, int pos);
list deletethis(list list);
list deleteitem(list list, int pos);
void clearlist(list list);

// utilita di ricerca nella lista
int searchposix(item item, list list);
list searchitem(item item, list list);
item extractthis(list list);
item extractitem(list list, int pos);

// utilita avanzate lista
list additem(item item,list list, int pos);
list reloaditem(item item, list list);
list copylist(list list);
list upplist(list list);


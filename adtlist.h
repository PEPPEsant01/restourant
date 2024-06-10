#ifndef ADTLIST_H
#define ADTLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    float price;
    //char **ingredients;
    int date;
    int shipped;
} data;

typedef struct list{
    struct list *next;
    struct list *prec;
    data item;
    int *count;
} list;

data extractitem(list *list, int position);
data extractthis(list *list);
list* movelist(list *list, int position);
list* headlist(list *list);
list* taillist(list *list);
list* newlist(data item);
list* catlist(list *list1, list *list2);
list* newlistnumbered(data *item, int numbered);
list* deleteitem(list *list, int posixion);
list* searchitem(data *item, list *list);
int searchposix(data *item, list *list);
list* precelement(list *list);
list* nextelement(list *list);
int listvalid(list *list);
list* copylist(list *list1);
list* upplist(list *list1);
int listcount(list *list);

#endif

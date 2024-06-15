#include <stdio.h>
#include <stdlib.h>


typedef struct data *item;
struct data{
    char *name;
    float price;
    int date;
    int shipped;
};

// utilita di base gestione dati
item newitem(char *name, float price, int date, int shipped);
item copyitem(item item);
int compareitem(item item1, item item2);
void clearitem(item item);

// ottenimento dati dell'oggetto
char *getname(item item);
float getprice(item item);
int getdate(item item);
int getshipped(item item);

// aggiornamento dati dell'oggetto
item setshipped(item item);
item setorder(item item);
item updatedate(item item);

// utilita aggiuntive
item orderitem(item item);




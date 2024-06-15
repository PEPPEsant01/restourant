
#include "item.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    char *name = "testitem";
    float price = 6.66;
    int shipped = 1;
    int date = 20160101;
    item testitem = newitem(name,price,date,shipped);
    //list testdata = newlist(testitem);
    
    //item testitem = extractthis(testdata);
    
    //fprintf(stdout, "%d\n", getdate(testitem));
    //fprintf(stdout, "%s\n", getname(testitem));
    //updatedate(testitem);
    //fprintf(stdout, "%d\n", getdate(testitem));
    //fprintf(stdout, "%f\n", testitem->price);
    //fprintf(stdout, "%d", testitem->shipped);


}
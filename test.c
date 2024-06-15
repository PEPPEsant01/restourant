#include "adtlist.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    
    list testdata = newlist(newitem("testitem",6.66,0,2));
    
    fprintf(stdout, "%d\n", getdate(extractthis(testdata)));
    fprintf(stdout, "%s\n", getname(extractthis(testdata)));
    updatedate(extractthis(testdata));
    fprintf(stdout, "%d\n", getdate(extractthis(testdata)));
    //fprintf(stdout, "%f\n", testitem->price);
    //fprintf(stdout, "%d", testitem->shipped);


}
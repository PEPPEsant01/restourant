#include "adtarea.h"
#include <stdio.h> // Includi la libreria standard per le operazioni di input/output
#include <stdlib.h> // Includi la libreria standard per l'allocazione dinamica della memoria


// Dichiarazione dei prototipi delle funzioni



int screen(int more) {
    int choise = 666;
    int loadmenu = 4;
    if (1 == more) {
        loadmenu = 11;
    }
    while (-1 >= choise || loadmenu < choise) {
        fprintf(stdout, "!!!selezionare la modalita di funzionamento del programma!!!\n");
        fprintf(stdout, "\n\n");
        fprintf(stdout, "-1:\t\t\tESCI dal programma\n");
        fprintf(stdout, "0:\t\t\tresetta il programma(cancella il menu caricato!!!)\n");
        fprintf(stdout, "\n\n");
        fprintf(stdout, "1:\t\t\tstampa le informazioni relative al programma (licenze e copyright)\n");
        fprintf(stdout, "2:\t\t\tstampa il menu\n");
        fprintf(stdout, "3:\t\t\tsettare un proprio ordine\n");
        fprintf(stdout, "4:\t\t\tcaricare un ordine da file\n");
        if (1 == more) {
            fprintf(stdout, "5:\t\t\testendi un proprio ordine (9: eseguito automaticamente)\n");
            fprintf(stdout, "6:\t\t\testendi un ordine da file (9: eseguito automaticamente)\n");
            fprintf(stdout, "7:\t\t\tstampa gli ordini appena arrivati\n");
            fprintf(stdout, "8:\t\t\tstampa gli ordini in arrivo\n");
            fprintf(stdout, "9:\t\t\tcancella gli ordini appena arrivati\n");
            fprintf(stdout, "10:\t\t\tseleziona e contrasegna come arrivato un ordine\n");
            fprintf(stdout, "\n\n");
            fprintf(stdout, "11:\t\t\telimina gli ordini di un tavolo\n");
        }
        
        fscanf(stdin, "%d", choise);
    }
    return choise;
}

void cleanareaorder(area sala, int pos) {
    if (NULL == sala) {
        return;
    }
    table table = gettable(sala, pos);
    tablerefresh(table);
    
    return;
}



int selecttable(area sala) {
    area temp = sala;
    if (NULL == temp) {
        return -1;
    }
    int size = areasize(temp);
    int selection = 0;
    
    do {
        printarea(temp);
        fprintf(stdout, "seleziona un tavolo (scrivi il suo id):\n");
        fscanf(stdin, "%d", selection);
    } while (NULL == gettable(temp, selection));
    return selection;
}

void printlicense() {
    fprintf(stdout, "\n\nil codice sorgente è libero e disponibile, distribuito sotto licenze BSD 4-clause e WTFPL\n");
    fprintf(stdout, "l'utente può modificare e distribuire il codice sorgente\n");
    fprintf(stdout, "può redistribuire i binari compilati con o senza modifiche\n");
    fprintf(stdout, "a patto di rispettare il copyright e le seguenti licenze\n\n");

    fprintf(stdout, "BSD 4-clause e WTFPL sotto copyright di:\n");
    fprintf(stdout, "Copyright (c) PEPPEsant01\n");
    fprintf(stdout, "Copyright (c) g.santarsiero7@studenti.unisa.it\n");
    fprintf(stdout, "Copyright (c) santarsieropeppe@live.com\n\n");
    
    fprintf(stdout, "BUON USO CONSAPEVOLE!!!\n\n");
    return;
}





int control(FILE *fp) {
    area sala = NULL;
    list menu = newmenu(fp);
    table temp = NULL;
    int selection = 0;
    int more = 0;
    char *filename;
    if (fp != NULL) {
        fclose(fp);
    }

    

        while (1) {

            switch (screen(more)) {
                case -1:
                    return 1;
                case 0:
                    return 0;
                    break;
                case 1:
                    printlicense();
                    break;
                case 2:
                    printlist(menu, 0);
                    break;
                case 3:
                    if (sala == NULL){
                        sala = newArea(newtable(menu,NULL),menu);
                        more = 1;
                    } else {
                        addArea(sala, newtable(menu,NULL));
                    }
                    break;
                case 4:
                    filename = calloc(666,sizeof(char));
                    fprintf(stdout, "inserisci il nome del file da leggere:\n");
                    fscanf(stdin, "%s", filename);
                    fp = fopen(filename, "r");
                    if (NULL == fp){
                        fprintf(stdout, "file non trovato\n");
                        break;
                    }
                    if (sala == NULL){
                        newArea(newtable(menu,fp),menu);
                        more = 1;
                    } else {
                        addArea(sala, newtable(menu,fp));
                    }
                    fclose(fp);
                    break;
                case 5:
                    // estendi un proprio ordine (9: eseguito automaticamente
                    temp = gettable(sala, selecttable(sala));
                    if (NULL == temp) {
                        break;
                    }
                    temp = addorder(temp, getmenu(sala), NULL);

                    break;
                case 6:
                    // estendi un ordine da file (9: eseguito automaticamente
                    filename = calloc(666,sizeof(char));
                    fprintf(stdout, "inserisci il nome del file da leggere:\n");
                    fscanf(stdin, "%s", filename);
                    fp = fopen(filename, "r");
                    if (NULL == fp){
                        fprintf(stdout, "file non trovato\n");
                        break;
                    }
                    temp = gettable(sala, selecttable(sala));
                    if (NULL == temp) {
                        break;
                    }
                    temp = addorder(temp, getmenu(sala), fp);
                    fclose(fp);

                    break;
                case 7:
                    // stampa gli ordini appena arrivati
                    temp = gettable(sala, selecttable(sala));
                    if (NULL == temp) {
                        break;
                    }
                    printshipped(temp);

                    break;
                case 8:
                    // stampa gli ordini in arrivo
                    temp = gettable(sala, selecttable(sala));
                    if (NULL == temp) {
                        break;
                    }
                    printunshipped(temp);

                    break;
                case 9:
                    cleanareaorder(sala, selecttable(sala));
                    

                    break;
                case 10:

                    temp = gettable(sala, selecttable(sala));
                    if (NULL == temp) {
                        break;
                    }
                    fprintf(stdout, "tavolo numero: %d\n", getnumber(temp));
                    printorder(temp);
                    selection = 0;
                    do {
                        fprintf(stdout, "seleziona il piatto da contrassegnare spedito\n");
                        fscanf(stdin, "%d", selection);
                    } while (0 >= selection || selection > tableordersize(temp));
                    temp = markorder(temp, selection);

                    break;
                case 11:
                    
                    selection = 0;
                    do {
                        printarea(sala);
                        fprintf(stdout, "seleziona la posizione del tavolo da eliminare:\n");
                        fscanf(stdin, "%d", selection);
                        } while (0 <= selection && selection < areasize(sala));
                    sala = deletetable(sala, selection);
                    if (NULL == sala) {
                        more = 0;
                    }
                    break;
        
                }


            
        }
    
}


int main(int argc, char *argv[]) {

    char *filename = calloc(666,sizeof(char));
    FILE *fp;
    if (argc > 1) {
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stdout, "vuoi leggere da file? (1 per confermare, altro per negare):\n");
        int read = 0;
        fscanf(stdin, "%d", &read);
        if (1 == read) {
            fprintf(stdout, "inserisci il nome del file da leggere:\n");
            fscanf(stdin, "%s", filename);
            fp = fopen(filename, "r");
            if (NULL == fp){
                fprintf(stdout, "file non trovato\n");
                }
            } else {
                fp = NULL;
            }
        

    }

    int mode = 0;

    while (0 == mode){
        mode = control(NULL);
    }

}

#include "menu.h"
#include <stdio.h> // Includi la libreria standard per le operazioni di input/output
#include <stdlib.h> // Includi la libreria standard per l'allocazione dinamica della memoria

// Dichiarazione dei prototipi delle funzioni

int main(int argc, char *argv[]) {

  list *menu;
  table *tavoli;
  if (argc > 1) {
  }
}

int menu() {
  int choise = 666;
  while (-1 >= choise || 11 < choise) {
    fprintf(stdout,
            "!!!selezionare la modalita di funzionamento del programma!!!\n");
    fprintf(stdout, "\n\n");
    fprintf(stdout, "-1:\t\t\tESCI dal programma\n");
    fprintf(stdout,
            "0:\t\t\tresetta il programma(cancella il menu caricato!!!)\n");
    fprintf(stdout, "\n\n");
    fprintf(stdout, "1:\t\t\tstampa le informazioni relative al programma "
                    "(licenze e copyright)\n");
    fprintf(stdout, "2:\t\t\tstampa il menu\n");
    fprintf(stdout, "3:\t\t\tsettare un proprio ordine\n");
    fprintf(stdout, "4:\t\t\tcaricare un ordine da file\n");
    fprintf(
        stdout,
        "5:\t\t\testendi un proprio ordine (9: eseguito automaticamente)\n");
    fprintf(
        stdout,
        "6:\t\t\testendi un ordine da file (9: eseguito automaticamente)\n");
    fprintf(stdout, "7:\t\t\tstampa gli ordini appena arrivati\n");
    fprintf(stdout, "8:\t\t\tstampa gli ordini in arrivo\n");
    fprintf(stdout, "9:\t\t\tcancella gli ordini appena arrivati\n");
    fprintf(stdout,
            "10:\t\t\tseleziona e contrasegna come arrivato un ordine\n");
    fprintf(stdout, "\n\n");
    fprintf(stdout, "11:\t\t\telimina gli ordini di un tavolo\n");
    fscanf(stdin, "%d", choise);
  }
  return choise;
}

void resetmenu(list *list) { deletelist(list); }

list *loadmenu(FILE *fp) {}

void control(FILE *fp) {

  while (1) {

    list *menu = loadmenu(fp);

    while (1) {

      switch (menu();) {
      case -1:
        return;
      case 0:
        printf("Monday");
        break;
      case 1:
        printf("Monday");
        break;
      case 2:

        break;
      case 3:

        break;
      case 4:

        break;
      case 5:

        break;
      case 6:

        break;
      case 7:

        break;
      case 8:

        break;
      case 9:

        break;
      case 10:

        break;
      case 11:

        break;
      case 12:

        break;
      case 13:

        break;
      }
      if (-1 == posix) {
        return
      }
    }
  }
}

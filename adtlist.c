#include "adtlist.h"
#include <stdio.h> // Includi la libreria standard per le operazioni di input/output
#include <stdlib.h> // Includi la libreria standard per l'allocazione dinamica della memoria

int searchposix(data *item, list *list) {
  int i = 0;
  list *posil = headlist(list);
  posil = headlist(list);
  while (NULL != posil) {

    if (posil->item->name == *item->name) {
      return i;
    }

    posil = posil->next;
    i++;
  }
  return -1;
}

list *reloaditem(data item, list *list) {
  if (NULL == list) {
    return NULL;
  }
  list->item = item;
  return list;
}

list *searchitem(data *item, list *list) {

  list *posil = headlist(list);
  while (NULL != posil) {

    if (posil->item->name == *item->name) {
      return posil;
    }

    posil = posil->next;
  }
  return NULL;
}

list *deleteitem(list *list, int posixion) {
  if (0 > posixion || list->count <= posixion || NULL == list) {
    return NULL;
  }
  list *posil = movelist(list, posixion);
  if (NULL == posil) {
    return NULL;
  }
  list *prec = posil->prec;
  list *next = posil->next;
  posil->count -= 1;
  free(posil);
  if (NULL != prec) {
    prec->next = next;
  }
  if (NULL != next) {
    next->prec = prec;
    return headlist(next);
  }
  if (NULL == next && NULL == prec) {

    return NULL;
  }
  return headlist(prec);
}

list *headlist(list *list) {
  list *posil = list;
  while (NULL != posil->prec) {
    posil = posil->prec;
  }
  return posil;
}

list *nextelement(list *list) { 
    return list->next; 
}

list *taillist(list *list) {
  list *posil = list;
  while (NULL != posil->next) {
    posil = posil->next;
  }
  return posil;
}

list *precelement(list *list) { 
    return list->prec; 
}

int listvalid(list *list) {
  if (NULL != list) {
    return 1;
  }
  return 0;
}

list *recount(list *list) {
  list *posil = taillist(list);
  int *count = (int *)calloc(1, sizeof(int));
  if (NULL == count) {
    return NULL; // Verifica che l'allocazione della memoria abbia successo
  }
  *count = 0;
  while (posil != NULL) {

    free(posil->count);
    posil->count = count;

    (*count)++;
    posil = posil->prec;
  }
  return posil;
}

list *movelist(list *list, int posixion) {
  if (posixion < 0 || posixion >= *(list->count)) {
    return NULL;
  }
  list *posil = headlist(list);
  for (int i = 0; i < posixion; i++) {
    posil = posil->next;
  }
  return posil;
}

data extractitem(list *list, int posixion) {
  list *posil = movelist(list, posixion);
  if (NULL != posil) {
    return posil->item;
  }

  return NULL;
}

data extractthis(list *list) {
  list *posil = list;
  if (NULL != posil) {
    return posil->item;
  }

  return NULL;
}

list *newnumberedinternal(data *item, int numbered, list *prec) {
  if (numbered <= 0) {
    return NULL;
  }
  list *newlist = (list *)calloc(1, sizeof(list));
  if (NULL == newlist) {
    return NULL; // Verifica che l'allocazione della memoria abbia successo
  }
  newlist->item = *item;
  newlist->prec = prec;
  newlist.count = (int *)calloc(1, sizeof(int));
  if (NULL == newlist->count) {
    free(newlist); // Libera la memoria se l'allocazione di count fallisce
    return NULL;
  }
  newlist->next = newnumberedinternal(item + 1, numbered - 1, newlist);
  return newlist;
}

list *newlist(data item) {
  list *newlist = (list *)calloc(1, sizeof(list));
  if (NULL == newlist) {
    return NULL; // Verifica che l'allocazione della memoria abbia successo
  }
  newlist->item = item;
  newlist->next = NULL;
  newlist->prec = NULL;
  newlist.count = (int *)calloc(1, sizeof(int));
  if (NULL == newlist->count) {
    free(newlist); // Libera la memoria se l'allocazione di count fallisce
    return NULL;
  }
  *(newlist->count) = 1;
  return newlist;
}

list *catlist(list *list1, list *list2) {
  if (NULL == list1) {
    return headlist(list2);
  }
  if (NULL == list2) {
    return headlist(list1);
  }
  list *posil1 = taillist(list1);
  list *posil2 = headlist(list2);

  posil1->next = posil2;
  posil2->prec = posil1;

  return recount(list1);
}

list *newlistnumbered(data *item, int numbered) {
  list *newlist = newnumberedinternal(item, numbered, NULL);
  return recount(newlist);
}

list *copylist(list *list) {

  if (NULL == list) {
    return NULL;
  }
  list *posil = headlist(list);

  list *copy = newlist(extractthis(posil));
  copy.prec = NULL;
  while (NULL != posil.next) {
    posil = nextelement(posil);
    copy.next = newlist(extractthis(posil));
    copy = nextelement(copy);
    copy.prec = precelement(copy);
    if (NULL == copy) {
      return NULL;
    }
  }
  copy.next = NULL;

  return recount(copy);
}

list *upplist(list *list1) {

  if (NULL == list) {
    return NULL;
  }
  list *posil = nextelement(list);
  if (NULL == posil) {
    return NULL;
  }
  list *copy = newlist(extractthis(posil));
  copy.prec = NULL;
  while (NULL != posil.next) {
    posil = nextelement(posil);
    copy.next = newlist(extractthis(posil));
    copy = nextelement(copy);
    copy.prec = precelement(copy);
    if (NULL == copy) {
      return NULL;
    }
  }
  copy.next = NULL;

  return recount(copy);
}

int listcount(list *list) {
  if (NULL == list) {
    return 0;
  }
  return *(list->count);
}

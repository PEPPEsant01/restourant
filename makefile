ristorant: main.o item.o adtlist.o menu.o adtarea.o
	gcc main.o item.o adtlist.o menu.o adtarea.o -o ristorant

item.o: item.c 
	gcc -c item.c
	
adtlist.o: adtlist.c
	gcc -c adtlist.c 
	
menu.o: menu.c
	gcc -c menu.c

adtarea.o: adtarea.c
	gcc -c adtarea.c
	

main.o: main.c
	gcc -c main.c -std=c99



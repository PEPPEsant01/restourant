ristorant: main.o menu.o adtlist.o menu.h adtlist.h
	gcc main.o menu.o adtlist.o menu.h adtlist.h -o ristorant
	
adtlist.o: adtlist.c adtlist.h
	gcc -c adtlist.c adtlist.h 
	
menu.o: menu.c menu.h adtlist.h
	gcc -c menu.c menu.h adtlist.h 
	
main.o: main.c menu.o menu.h
	gcc -c main.c menu.o menu.h -std=c99
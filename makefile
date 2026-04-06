# addressbook.exe: main.o file.o contact.o validation.o
# 	gcc -o addressbook.exe main.o file.o contact.o validation.o
# main.o:main.c
# 	gcc -c main.c
# file.o:file.c
# 	gcc -c file.c
# contact.o:contact.c
# 	gcc -c contact.c
# validation.o:validation.c
# 	gcc -c validation.c
# clean:
# 	rm *.exe *.o

OBJ:=$(patsubst %.c,%.0,$(wildcard*.c))
cal.exe:$(OBJ)
gcc -o $@$^
clean:
	rm *.exe*.o
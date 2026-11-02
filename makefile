exe: main.o macro.o header.o comment.o
	gcc main.o macro.o header.o comment.o -o exe

main.o: main.c
	gcc -c main.c

macro.o: macro.c
	gcc -c macro.c

header.o: header.c
	gcc -c header.c

comment.o: comment.c
	gcc -c comment.c

clear:
	@echo "Cleaning up....."
	@rm -v *.o exe

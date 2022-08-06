all: compactador descompactador

compactador: compacta.o treeList.o arvbin.o caractere.o bitmap.o
	@gcc -o saidacomp compacta.o treeList.o arvbin.o caractere.o bitmap.o

descompactador: descompacta.o treeList.o arvbin.o caractere.o bitmap.o
	@gcc -o saidades descompacta.o treeList.o arvbin.o caractere.o bitmap.o

compacta.o: compacta.c treeList.h bitmap.h
	@gcc -o compacta.o compacta.c -c

descompacta.o: descompacta.c treeList.h bitmap.h
	@gcc -o descompacta.o descompacta.c -c

treeList.o: treeList.h treeList.c
	@gcc -o treeList.o treeList.c -c

arvbin.o: arvbin.c arvbin.h
	@gcc -o arvbin.o arvbin.c -c

caractere.o: caractere.c caractere.h
	@gcc -o caractere.o caractere.c -c

bitmap.o: bitmap.c bitmap.h
	@gcc -o bitmap.o bitmap.c -c
	

clean:
	@rm -rf *.o saidacomp saidades
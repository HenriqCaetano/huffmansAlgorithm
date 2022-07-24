saida: compacta.o treeList.o arvbin.o caractere.o
	@gcc -o saida compacta.o treeList.o arvbin.o caractere.o

treeList.o: treeList.h treeList.c
	@gcc -o treeList.o treeList.c -c

arvbin.o: arvbin.c arvbin.h
	@gcc -o arvbin.o arvbin.c -c

caractere.o: caractere.c caractere.h
	@gcc -o caractere.o caractere.c -c

clean:
	@rm -rf *.o ~saida
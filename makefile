saida: bitmaptester.o bitmap.o
	@gcc -o saida bitmaptester.o bitmap.o

bitmap.o: bitmap.h
	@gcc -o bitmap.o bitmap.c -c

bitmaptester.o: bitmaptester.c bitmap.h
	@gcc -o bitmaptester.o bitmaptester.c -c

clean:
	@rm -rf *.o ~saida
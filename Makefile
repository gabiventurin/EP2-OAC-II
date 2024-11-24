#Configurando o Makefile

ep: readAndConvert matrizes knn
	gcc -g readAndConvert.o matrizes.o knn.o fullCodeNoParallel.c -o ep

readAndConvert:
	gcc -c -g -o readAndConvert.o readAndConvert.c

matrizes:
	gcc -c -g -o matrizes.o matrizes.c

knn:
	gcc -c -g -o knn.o knn.c

pedantic: readAndConvert_pedantic matrizes_pedantic knn_pedantic
	gcc -ansi -std=c99 -pedantic -Wall -Werror readAndConvert_pedantic.o matrizes_pedantic.o knn_pedantic.o fullCodeNoParallel.c -o ep

readAndConvert_pedantic:
	gcc -ansi -std=c99 -pedantic -Wall -Werror -c -o readAndConvert_pedantic.o readAndConvert.c

matrizes_pedantic:
	gcc -ansi -std=c99 -pedantic -Wall -Werror -c -o matrizes_pedantic.o matrizes.c

knn_pedantic:
	gcc -ansi -std=c99 -pedantic -Wall -Werror -c -o knn_pedantic.o knn.c

clean:
	rm -rf ep *.o readAndConver matrizes knn fullCodeNoParallel

#Configurando o Makefile
ep: readAndConvert matrizes knn
	gcc -g readAndConvert.o matrizes.o knn.o main.c -fopenmp -o ep

parallelEP: readAndConvert matrizes knn
	gcc -g readAndConvert.o matrizes.o knn.o fullCodeParallel.c -fopenmp -o ep

normalEP: readAndConvert matrizes knn
	gcc -g readAndConvert.o matrizes.o knn.o fullCodeNoParallel.c -fopenmp -o ep

readAndConvert:
	gcc -c -g -o readAndConvert.o readAndConvert.c

matrizes:
	gcc -c -g -fopenmp -o matrizes.o matrizes.c

knn:
	gcc -c -g -fopenmp -o knn.o knn.c 

pedantic_parallel: readAndConvert_pedantic matrizes_pedantic knn_pedantic
	gcc -ansi -std=c99 -pedantic -Wall -Werror readAndConvert_pedantic.o matrizes_pedantic.o knn_pedantic.o fullCodeParallel.c -o ep

pedantic_normal: readAndConvert_pedantic matrizes_pedantic knn_pedantic
	gcc -ansi -std=c99 -pedantic -Wall -Werror readAndConvert_pedantic.o matrizes_pedantic.o knn_pedantic.o fullCodeNoParallel.c -o ep

readAndConvert_pedantic:
	gcc -ansi -std=c99 -pedantic -Wall -Werror -c -o readAndConvert_pedantic.o readAndConvert.c

matrizes_pedantic:
	gcc -ansi -std=c99 -pedantic -Wall -Werror -c -o matrizes_pedantic.o matrizes.c

knn_pedantic:
	gcc -ansi -std=c99 -pedantic -Wall -Werror -c -o knn_pedantic.o knn.c

clean:
	rm -rf ep *.o readAndConver matrizes knn fullCodeNoParallel fullCodeParallel

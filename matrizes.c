#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Função para criar a matriz
void createMatriz(int n, int h, int w, double* array, double result[][w]) {
    int limitindex = n - w - h + 2; // Índice limite para as linhas
    int i, j;

    for (i = 0; i < limitindex; i++) {
        for (j = 0; j < w; j++) {
            result[i][j] = array[i + j]; // Preenche cada linha da matriz com w elementos consecutivos
        }
    }
}

void createMatrizParallel(int n, int h, int w, double* array, double result[][w], int nThreads) {
    int limitindex = n - w - h + 2; // Índice limite para as linhas

    #pragma omp parallel num_threads(nThreads)
    {
        int i;
        #pragma omp for
            for (i = 0; i < limitindex; i++) {
                for (int j = 0; j < w; j++) {
                    result[i][j] = array[i + j]; // Preenche cada linha da matriz com w elementos consecutivos
                }
            }
    }
}


void createYtrain(int n, int h, int w, int ytrainSize, double* xtrain, double* ytrain){

    int xTrainPoint = h + w - 1;

    for(int i = 0; i<ytrainSize; i++){
        ytrain[i] = xtrain[xTrainPoint];
        xTrainPoint++;
    }

    return;
}

// TESTES
/*
int main() {
    // Parametros de entrada
    int h = 1;
    int w = 3;

    int xtrainsize = 5;
    double xtrain[5] = {7.0, 8.0, 9.5, 2.0, 11.1};

    int xtestsize = 10;
    double xtest[10] = {10.0, 7.55, 50.0, 3.5, 3.7, 2.0, 4.67, 8.55, 9.45, 60.4};
    
    // Calcula o número de linhas na matriz resultante
    int rows = xtrainsize - w - h + 2;

    // Matriz para armazenar o resultado
    double result[rows][w];
    createMatriz(xtrainsize, h, w, xtrain, result);

    / Imprime a matriz resultante
    printf("Matriz resultante:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < w; j++) {
            printf("%.2f ", result[i][j]);
        }
        printf("\n");
    }

   int ytrainSize = xtestsize - w - h + 1;
   double* ytrain = (double*)malloc(ytrainSize * sizeof(double));

   createYtrain(xtestsize, h, w, ytrainSize, xtest, ytrain);

   int sizeYtrain = xtestsize - h - w + 1;

   for(int i = 0; i<sizeYtrain; i++){
    printf("%.2lf\n", ytrain[i]);
   }

   int x = findArraySize(xtest);

   printf("%i\n", x);

    return 0;
}*/
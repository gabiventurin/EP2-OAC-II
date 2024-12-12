#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "readAndConvert.h"
#include "matrizes.h"
#include "knn.h"

int main(){

    // DETERMINACAO DOS ARQUIVOS
    char* xtrain1 = "data/dados_xtrain.txt";
    char* xtest1 = "data/dados_xtest_1000000.txt";
    char* ytest = "output/YtestPar1000000.txt";

    printf("Arquivos determinados!\nLendo arquivos e colocando em arrays...\n");

    // LEITURA DOS ARQUIVOS

    double* arrayXtrain1 = readFileAndConvertToArray(xtrain1);
    double* arrayXtest1 = readFileAndConvertToArray(xtest1);

    printf("Quantas iterações devem ser realizadas?\n>");
    
    int iteracoes;

    scanf("%i", &iteracoes);
    
    printf("Arquivos colocados nos arrays!\nExecutando %i vezes...\n", iteracoes);

    double tempos[iteracoes];

    for(int i = 0; i<iteracoes; i++){
        tempos[i] = iteracoes;
    }

    for(int i = 0; i < iteracoes; i++){

        double timeInit = omp_get_wtime();
        
        // agora os arrays de xtrain1 e xtest1 estão, respectivamente, em arrayXtrain1 e arrayXtest1

        // CRIACAO DAS MATRIZES
        int nXtrain1 = getNumberOfLines(xtrain1);
        int nXtest1 = getNumberOfLines(xtest1);

        int h = 1;
        int w = 3;

        int rowsXtrain1 = nXtrain1 - w - h + 2;
        int rowsXtest1 = nXtest1 - w - h + 2;

        double matrixXtrain1[rowsXtrain1][w];
        double matrixXtest1[rowsXtest1][w];

        createMatrizParallel(nXtrain1, h, w, arrayXtrain1, matrixXtrain1);
        createMatrizParallel(nXtest1, h, w, arrayXtest1, matrixXtest1);

        // CRIACAO DO YTRAIN

        int ytrain1Size = nXtrain1 - w - h + 1;
        double* ytrain1 = (double*)malloc(ytrain1Size * sizeof(double));
        
        createYtrain(nXtrain1, h, w, ytrain1Size, arrayXtrain1, ytrain1);

        // REALIZACAO DO KNN

        double* ytest1 = knnParallel(w, nXtrain1, nXtest1, matrixXtrain1, matrixXtest1, ytrain1, 4);

        double timeEnd = omp_get_wtime();
        
        // COLOCAÇÃO DOS RESULTADOS EM UM ARQUIVO E FREE'S

        tempos[i] = timeEnd - timeInit;

        readArrayAndConvertToFile(ytest1, nXtest1, ytest);

        free(ytrain1);
    }
    
    printf("Tempo de cada iteração:\n");

    for(int i = 0; i<iteracoes; i++){
        printf("> %i: %.6lf s\n", i+1, tempos[i]);
    }

    printf("Calculando tempo médio em %i iterações...\n", iteracoes);

    double meanTime = 0;

    for(int i = 0; i<iteracoes; i++){
        meanTime += tempos[i];
    }
    meanTime = meanTime/iteracoes;

    printf("Tempo médio: %.6lf s\nExecução finalizada!\n", meanTime);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "readAndConvert.h"
#include "matrizes.h"
#include "knn.h"

int main(){

    // DETERMINACAO DOS ARQUIVOS
    char* xtrain = "data/dados_xtrain.txt";
    char* xtest = "data/dados_xtest_1000000.txt";
    char* ytest = "output/YtestPar1000000.txt";

    printf("Arquivos determinados!\nLendo arquivos e colocando em arrays...\n");

    // LEITURA DOS ARQUIVOS

    double* arrayXtrain1 = readFileAndConvertToArray(xtrain);
    double* arrayXtest1 = readFileAndConvertToArray(xtest);

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
        int nXtrain = getNumberOfLines(xtrain);
        int nXtest = getNumberOfLines(xtest);

        int h = 1;
        int w = 3;

        int rowsXtrain1 = nXtrain - w - h + 2;
        int rowsXtest1 = nXtest - w - h + 2;

        double matrixXtrain1[rowsXtrain1][w];
        double matrixXtest1[rowsXtest1][w];

        createMatrizParallel(nXtrain, h, w, arrayXtrain1, matrixXtrain1, 4);
        createMatrizParallel(nXtest, h, w, arrayXtest1, matrixXtest1, 4);

        // CRIACAO DO YTRAIN

        int ytrainSize = nXtrain - w - h + 1;
        double* arrayYtrain = (double*)malloc(ytrainSize * sizeof(double));
        
        createYtrain(nXtrain, h, w, ytrainSize, arrayXtrain1, arrayYtrain);

        // REALIZACAO DO KNN

        double* arrayYtest = knnParallel(w, nXtrain, nXtest, matrixXtrain1, matrixXtest1, arrayYtrain, 4);

        double timeEnd = omp_get_wtime();
        
        // COLOCAÇÃO DOS RESULTADOS EM UM ARQUIVO E FREE'S

        tempos[i] = timeEnd - timeInit;

        readArrayAndConvertToFile(arrayYtest, nXtest, ytest);

        free(arrayYtrain);
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
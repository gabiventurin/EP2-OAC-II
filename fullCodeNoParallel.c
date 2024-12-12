#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "readAndConvert.h"
#include "matrizes.h"
#include "knn.h"

int main(){

    // DETERMINACAO DOS ARQUIVOS
    char* xtrain = "data/dados_xtrain.txt";
    char* xtest = "data/dados_xtest_10000000.txt";
    char* ytest = "output/Ytest.txt";

    printf("Arquivos determinados!\nLendo arquivos e colocando em arrays...\n");

    // LEITURA DOS ARQUIVOS

    double* arrayXtrain = readFileAndConvertToArray(xtrain);
    double* arrayXtest = readFileAndConvertToArray(xtest);

    printf("Quantas iterações devem ser realizadas?\n>");
    
    int iteracoes;

    scanf("%i", &iteracoes);
    
    printf("Arquivos colocados nos arrays!\nExecutando %i vezes...\n", iteracoes);

    double tempos[iteracoes];

    for(int i = 0; i<iteracoes; i++){
        tempos[i] = iteracoes;
    }

    for(int i = 0; i < iteracoes; i++){

        double timeInit = (double) clock();
        timeInit = timeInit/CLOCKS_PER_SEC;

        // agora os arrays de xtrain e xtest estão, respectivamente, em arrayXtrain e arrayXtest

        // CRIACAO DAS MATRIZES
        int nXtrain = getNumberOfLines(xtrain);
        int nXtest = getNumberOfLines(xtest);

        int h = 1;
        int w = 3;

        int rowsXtrain = nXtrain - w - h + 2;
        int rowsXtest = nXtest - w - h + 2;

        double matrixXtrain[rowsXtrain][w];
        double matrixXtest[rowsXtest][w];

        createMatriz(nXtrain, h, w, arrayXtrain, matrixXtrain);
        createMatriz(nXtest, h, w, arrayXtest, matrixXtest);

        // CRIACAO DO YTRAIN

        int ytrainSize = nXtrain - w - h + 1;
        double* arrayYtrain = (double*)malloc(ytrainSize * sizeof(double));
        
        createYtrain(nXtrain, h, w, ytrainSize, arrayXtrain, arrayYtrain);

        // REALIZACAO DO KNN

        double* arrayYtest = knn(w, nXtrain, nXtest, matrixXtrain, matrixXtest, arrayYtrain);

        double timeEnd = (double) clock();
        timeEnd = timeEnd / CLOCKS_PER_SEC;

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
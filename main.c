#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "readAndConvert.h"
#include "matrizes.h"
#include "knn.h"

int main(int argc, char ** argv){

    if(argc != 8){
        printf("Esse programa deve ser executado usando: %s xtrain.txt xtest.txt ytest.txt k h w numeroDeThreads\n", argv[0]);
        return 1;
    }

    // SEQUENCIAL //////////////////////////////////////////////////////////////////
    
    // DETERMINACAO DOS ARQUIVOS
    char* xtrain = argv[1];
    char* xtest = argv[2];
    char* ytest = argv[3];
    int k = atoi(argv[4]);
    int h = atoi(argv[5]);
    int w = atoi(argv[6]);
    int nThreads = atoi(argv[7]);

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

        double* arrayYtest = knn(w, k, nXtrain, nXtest, matrixXtrain, matrixXtest, arrayYtrain);

        double timeEnd = (double) clock();
        timeEnd = timeEnd / CLOCKS_PER_SEC;

        // COLOCAÇÃO DOS RESULTADOS EM UM ARQUIVO E FREE'S

        tempos[i] = timeEnd - timeInit;

        readArrayAndConvertToFile(arrayYtest, nXtest, ytest);

        free(arrayYtrain);
    }
    
    printf("Tempo de cada iteração sequencial:\n");

    for(int i = 0; i<iteracoes; i++){
        printf("> %i: %.6lf s\n", i+1, tempos[i]);
    }

    printf("Calculando tempo médio em %i iterações sequenciais...\n", iteracoes);

    double meanTime = 0;

    for(int i = 0; i<iteracoes; i++){
        meanTime += tempos[i];
    }
    meanTime = meanTime/iteracoes;

    printf("Tempo médio sequencial: %.6lf s\nExecução finalizada!\n", meanTime);


    // PARALELO ////////////////////////////////////////////////////////

    printf("Iniciando os testes em paralelo...\n");
    
    printf("Executando %i vezes...\n", iteracoes);

    for(int i = 0; i<iteracoes; i++){
        tempos[i] = iteracoes;
    }

    for(int i = 0; i < iteracoes; i++){

        double timeInit = omp_get_wtime();
        
        // agora os arrays de xtrain1 e xtest1 estão, respectivamente, em arrayXtrain1 e arrayXtest1

        // CRIACAO DAS MATRIZES
        int nXtrain = getNumberOfLines(xtrain);
        int nXtest = getNumberOfLines(xtest);

        int rowsXtrain = nXtrain - w - h + 2;
        int rowsXtest = nXtest - w - h + 2;

        double matrixXtrain[rowsXtrain][w];
        double matrixXtest[rowsXtest][w];

        createMatrizParallel(nXtrain, h, w, arrayXtrain, matrixXtrain, nThreads);
        createMatrizParallel(nXtest, h, w, arrayXtest, matrixXtest, nThreads);

        // CRIACAO DO YTRAIN

        int ytrainSize = nXtrain - w - h + 1;
        double* arrayYtrain = (double*)malloc(ytrainSize * sizeof(double));
        
        createYtrain(nXtrain, h, w, ytrainSize, arrayXtrain, arrayYtrain);

        // REALIZACAO DO KNN

        double* arrayYtest = knnParallel(w, k, nXtrain, nXtest, matrixXtrain, matrixXtest, arrayYtrain, nThreads);

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

    meanTime = 0;

    for(int i = 0; i<iteracoes; i++){
        meanTime += tempos[i];
    }
    meanTime = meanTime/iteracoes;

    printf("Tempo médio: %.6lf s\nExecução finalizada!\n", meanTime);


}
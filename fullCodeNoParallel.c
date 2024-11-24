#include <stdio.h>
#include <stdlib.h>
#include "readAndConvert.h"
#include "matrizes.h"
#include "knn.h"

int main(){

    // DETERMINACAO DOS ARQUIVOS
    char* xtrain1 = "data/Xtrain.txt";
    char* xtest1 = "data/Xtest.txt";
    char* ytest = "output/Ytest.txt";

    printf("Arquivos determinados!\nLendo arquivos e colocando em arrays...\n");

    // LEITURA DOS ARQUIVOS

    double* arrayXtrain1 = readFileAndConvertToArray(xtrain1);
    double* arrayXtest1 = readFileAndConvertToArray(xtest1);
    
    printf("Arquivos colocados nos arrays!\nCriando as matrizes do X...\n");

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

    createMatriz(nXtrain1, h, w, arrayXtrain1, matrixXtrain1);
    createMatriz(nXtest1, h, w, arrayXtest1, matrixXtest1);

    printf("Matrizes do X criadas!\nCriando YTrain...\n");

    // CRIACAO DO YTRAIN

    int ytrain1Size = nXtrain1 - w - h + 1;
    double* ytrain1 = (double*)malloc(ytrain1Size * sizeof(double));
    
    createYtrain(nXtrain1, h, w, ytrain1Size, arrayXtrain1, ytrain1);

    printf("YTrain criada! Realizando o KNN...\n");

    // REALIZACAO DO KNN

    double* ytest1 = knn(w, nXtrain1, nXtest1, matrixXtrain1, matrixXtest1, ytrain1);

    printf("KNN criado!\nColocando os resultados em um arquivo...\n");

    // COLOCAÇÃO DOS RESULTADOS EM UM ARQUIVO

    readArrayAndConvertToFile(ytest1, nXtest1);

    printf("Colocado no arquivo!\nPrograma finalizado!\n");
    return 0;
}
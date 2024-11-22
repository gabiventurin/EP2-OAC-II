// stdio.h ALREADY INCLUDED
#include <stdlib.h>
#include <readAndConvert.h> // already includes stdio.h because the type FILE* is needed in a header
#include <matrizes.h>
#include <knn.h>

int main(){

    // DETERMINACAO DOS ARQUIVOS
    char* xtrain1 = "data/Xtrain.txt";
    char* xtest1 = "data/Xtest.txt";
    char* ytest = "output/Ytest.txt";

    // LEITURA DOS ARQUIVOS

    double* arrayXtrain1;
    double* arrayXtest1;

    readFileAndConvertToArray(xtrain1, arrayXtrain1);
    readFileAndConvertToArray(xtest1, arrayXtest1);
    
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

    // REALIZACAO DO KNN

    

}
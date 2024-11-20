#include <stdio.h>
#include <stdlib.h>

int getNumberOfLines(char* fileString){
    int count = 0;
    char* tmp;

    while (fgets(tmp, 30, fileString)){
        count++;
    }

    return count;
}

double* readFileAndConvertToArray(char* f){

    FILE* fptr; // usado para passar pelo arquivo .txt
    char* numeroString; // usado para pegar apenas um numero do arquivo
    int sizeOfFile; // usado para armazenar o tamanho do arquivo
    char* fileString; // usado para guardar o conteúdo do arquivo
    char* numberString;
    int sizeOfArray; // usado para guardar o tamanho da matriz
    double* array; // usada para passar a matriz de retorno

    fseek(f, 0, SEEK_END); // vai ao fim do arquivo
    sizeOfFile = ftell(f); // marca o tamanho do arquivo
    fseek(f, 0, SEEK_SET); // volta para o inicio do arquivo

    fptr = fopen(f, "r"); // abre o arquivo

    if(fptr == NULL){
        printf("The file is invalid.");
        return;
    }

    fileString = (char*)malloc(sizeOfFile * sizeof(char)); // aloca o espaco para guardar o arquivo em uma string

    sizeOfArray = getNumberOfLines(fileString); // finds the number of lines in the array

    array = (double*)malloc(sizeOfArray * sizeof(double));

    for(int i = 0; i<sizeOfArray; i++){
        fgets(numberString, 30, fptr);
        int tmpDouble = atof(numberString);
        array[i] = tmpDouble;
    }

    return array;
}

/**
 * FUNÇÕES QUE FALTAM SER IMPLEMENTADAS :
 * - Conversão de array para string
 * - Colocação no arquivo YTest
 */
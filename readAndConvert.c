#include <stdio.h>
#include <stdlib.h>

int getNumberOfLines(FILE* fptr){
    int count = 0;
    char* tmp;

    while (fgets(tmp, 30, fptr)){
        count++;
    }

    return count;
}

void readFileAndConvertToArray(char* f, double* array){

    FILE* fptr; // usado para passar pelo arquivo .txt
    char* numeroString; // usado para pegar apenas um numero do arquivo
    int sizeOfFile; // usado para armazenar o tamanho do arquivo
    char* fileString; // usado para guardar o conteúdo do arquivo
    char* numberString;
    int sizeOfArray; // usado para guardar o tamanho da matriz
    
    fseek(f, 0, SEEK_END); // vai ao fim do arquivo
    sizeOfFile = ftell(f); // marca o tamanho do arquivo
    fseek(f, 0, SEEK_SET); // volta para o inicio do arquivo

    fptr = fopen(f, "r"); // abre o arquivo

    if(fptr == NULL){
        printf("The file is invalid.");
        return;
    }

    fileString = (char*)malloc(sizeOfFile * sizeof(char)); // aloca o espaco para guardar o arquivo em uma string

    sizeOfArray = getNumberOfLines(fptr); // finds the number of lines in the array

    array = (double*)malloc(sizeOfArray * sizeof(double));

    for(int i = 0; i<sizeOfArray; i++){
        fgets(numberString, 30, fptr);
        int tmpDouble = atof(numberString);
        array[i] = tmpDouble;
    }

    fclose(f);

    return;
}


void readArrayAndConvertToFile(double* array, int arraySize){
    FILE* fptr;
    
    fptr = fopen("output/Ytest.txt", "w");

    fprintf(fptr, "%lf", array[0]);

    fclose(fptr);

    fptr = fopen("output/Ytest.txt", "a");

    for(int i = 1; i<arraySize; i++){
        fprintf(fptr, "\n%lf", array[i]);
    }
    
    fclose(fptr);

    return;
} 


// USE FOR TESTS
/*
int main(){

    double array[] = {0.1, 2.0, 1234.3456};
    int arraySize = 3;

    readArrayAndConvertToFile(array, arraySize);

    printf("Done!");
}*/
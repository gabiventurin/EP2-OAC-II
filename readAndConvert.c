#include <stdio.h>
#include <stdlib.h>

int getNumberOfLines(char* f){
    FILE* fptr = fopen(f, "r");
    int count = 0;
    char c;

    for(c = getc(fptr); c != EOF; c = getc(fptr)){
        if(c=='\n') count++;
    }

    fclose(fptr);

    return count;
}

double* readFileAndConvertToArray(char* f){

    FILE* fptr; // usado para passar pelo arquivo .txt
    int sizeOfFile; // usado para armazenar o tamanho do arquivo
    char* fileString; // usado para guardar o conteúdo do arquivo
    char numberString[30];
    int sizeOfArray; // usado para guardar o tamanho da matriz
    double* array;
    
    fptr = fopen(f, "r"); // abre o arquivo

    fseek(fptr, 0, SEEK_END); // vai ao fim do arquivo
    sizeOfFile = ftell(fptr); // marca o tamanho do arquivo
    fseek(fptr, 0, SEEK_SET); // volta para o inicio do arquivo

    fileString = (char*)malloc(sizeOfFile * sizeof(char)); // aloca o espaco para guardar o arquivo em uma string

    sizeOfArray = getNumberOfLines(f); // finds the number of lines in the array

    array = (double*)malloc(sizeOfArray * sizeof(double));

    for(int i = 0; i<sizeOfArray; i++){
        if(fgets(numberString, 30, fptr)!=NULL){
            int tmpDouble = atof(numberString);
            array[i] = tmpDouble;
        }
    }

    fclose(fptr);

    return array;
}


void readArrayAndConvertToFile(double* array, int arraySize){
    FILE* fptr;
    
    fptr = fopen("output/Ytest.txt", "w");

    fprintf(fptr, "%.2lf", array[0]);

    for(int i = 1; i<arraySize; i++){
        fprintf(fptr, "\n%.2lf", array[i]);
    }
    
    fclose(fptr);

    return;
} 


// USE FOR TESTS

int main(){

    char* file = "data/teste.txt";

    double* teste = readFileAndConvertToArray(file);

    for(int i = 0; i<3; i++){
        printf("%.2lf\n", teste[i]);
    }

    int nXtrain1 = getNumberOfLines(file);

    double array[] = {0.1, 2.0, 1234.3456};
    int arraySize = 3;

    readArrayAndConvertToFile(array, arraySize);

    printf("Done!");
}
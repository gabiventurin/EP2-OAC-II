#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double* knn(int w, int xtrainSize, int xtestSize, double xtrain[xtrainSize][w], double xtest[xtestSize][w], double* ytrain) {
    double* ytest = (double*)malloc(xtestSize * sizeof(double));
    for (int i = 0; i < xtestSize; i++) {
        double* dist = (double*)malloc(xtrainSize * sizeof(double));
        for (int j = 0; j < xtrainSize; j++) {
            dist[j] = 0;
            for (int k = 0; k < w; k++) {
                dist[j] += (xtrain[j][k] - xtest[i][k]) * (xtrain[j][k] - xtest[i][k]);
            }
        }
        int* idx = (int*)malloc(xtrainSize * sizeof(int));
        for (int j = 0; j < xtrainSize; j++) {
            idx[j] = j;
        }
        for (int j = 0; j < xtrainSize; j++) {
            for (int k = j + 1; k < xtrainSize; k++) {
                if (dist[j] > dist[k]) {
                    double temp = dist[j];
                    dist[j] = dist[k];
                    dist[k] = temp;
                    int temp2 = idx[j];
                    idx[j] = idx[k];
                    idx[k] = temp2;
                }
            }
        }
        double sum = 0;
        for (int j = 0; j < w; j++) {
            sum += ytrain[idx[j]];
        }
        ytest[i] = sum / w;
    }
    return ytest;
}

double* knnParalel(int w, int xtrainSize, int xtestSize, double xtrain[xtrainSize][w], double xtest[xtestSize][w], double* ytrain) {
    double* ytest = (double*)malloc(xtestSize * sizeof(double)); // memory allocation for Ytest

    // ACHO QUE ESSE PEDACO QUE PRECISA SER PARALELIZADO PORQUE É NA ORGANIZAÇÃO DO YTEST QUE ESTÁ O CUSTO COMPUTACIONAL
    // PRECISA DIVIDIR O YTEST E DEIXAR O FOR I CERTINHO PRA ELE ACERTAR A LOCALIZAÇÃO DO RESULTADO NO ARRAY

    // OUTRO TESTE QUE PODE SER FEITO É PARALELIZAR INTERNAMENTE CADA ITERAÇÃO DE I
    #pragma omp paralel
    {
        int i;
        #pragma omp for // linha problema 1
        for (i = 0; i < xtestSize; i++) { // iterates over each xtest
            double* dist = (double*)malloc(xtrainSize * sizeof(double)); // memory allocation for the intermediary array
            for (int j = 0; j < xtrainSize; j++) {
                dist[j] = 0;
                for (int k = 0; k < w; k++) {
                    dist[j] += (xtrain[j][k] - xtest[i][k]) * (xtrain[j][k] - xtest[i][k]);
                }
            }
            int* idx = (int*)malloc(xtrainSize * sizeof(int));
            for (int j = 0; j < xtrainSize; j++) {
                idx[j] = j;
            }
            for (int j = 0; j < xtrainSize; j++) {
                for (int k = j + 1; k < xtrainSize; k++) {
                    if (dist[j] > dist[k]) {
                        double temp = dist[j];
                        dist[j] = dist[k];
                        dist[k] = temp;
                        int temp2 = idx[j];
                        idx[j] = idx[k];
                        idx[k] = temp2;
                    }
                }
            }
            double sum = 0;
            for (int j = 0; j < w; j++) {
                sum += ytrain[idx[j]];
            }
            ytest[i] = sum / w; // linha problema 2 :(
        }
    }
    return ytest;
}


//TESTES
/*
int main() {
    double xtrain[3][3] = {{4.99, 5.67, 9.134}, {7.567, 8.547, 9.88}, {5.32, 6.12, 9.44}};
    double xtest[7][3] = {{4.99, 5.67, 9.134}, {5.67, 9.134, 7.567}, {9.134, 7.567, 8.547}, {7.567, 8.547, 9.88}, {8.547, 9.88, 5.32}, {9.88, 5.32, 6.12}, {5.32, 6.12, 9.44}};
    double ytrain[6] = {7.567, 8.547, 9.88, 10.00, 10.768, 11.4356};
    int xtrainSize = 3;
    int xtestSize = 7;
    int w = 3;

    double* ytest = knn(w, xtrainSize, xtestSize, xtrain, xtest, ytrain);

    for (int i = 0; i < xtestSize; i++) {
        printf("%f\n", ytest[i]);
    }

    return 0;
}*/
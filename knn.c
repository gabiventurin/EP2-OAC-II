#include <stdio.h>
#include <stdlib.h>

double* knn(double(* xtrain)[3], double (* xtest)[3], double* ytrain, int m, int xtrainSize, int xtestSize) {
    double* ytest = (double*)malloc(xtestSize * sizeof(double));
    for (int i = 0; i < xtestSize; i++) {
        double* dist = (double*)malloc(xtrainSize * sizeof(double));
        for (int j = 0; j < xtrainSize; j++) {
            dist[j] = 0;
            for (int k = 0; k < m; k++) {
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
        for (int j = 0; j < m; j++) {
            sum += ytrain[idx[j]];
        }
        ytest[i] = sum / m;
    }
    return ytest;
}

int main() {
    double xtrain[3][3] = {{4.99, 5.67, 9.134}, {7.567, 8.547, 9.88}, {5.32, 6.12, 9.44}};
    double xtest[7][3] = {{4.99, 5.67, 9.134}, {5.67, 9.134, 7.567}, {9.134, 7.567, 8.547}, {7.567, 8.547, 9.88}, {8.547, 9.88, 5.32}, {9.88, 5.32, 6.12}, {5.32, 6.12, 9.44}};
    double ytrain[6] = {7.567, 8.547, 9.88, 10.00, 10.768, 11.4356};
    int xtrainSize = 3;
    int xtestSize = 7;
    int m = 3;

    double* ytest = knn(xtrain, xtest, ytrain, m, xtrainSize, xtestSize);

    for (int i = 0; i < xtestSize; i++) {
        printf("%f\n", ytest[i]);
    }

    return 0;
}
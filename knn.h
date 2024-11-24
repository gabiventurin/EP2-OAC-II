/**
 * Funcao que recebe um w, o tamanho de xtrain, o tamanho de xtest, xtrain, xtest e ytrain e retorna o array ytest
 */
double* knn(int w, int xtrainSize, int xtestSize, double xtrain[xtrainSize][w], double xtest[xtestSize][w], double* ytrain);
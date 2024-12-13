/**
 * Funcao sequencial que recebe um w, o tamanho de xtrain, o tamanho de xtest, xtrain, xtest e ytrain e retorna o array ytest
 */
double* knn(int w, int k, int xtrainSize, int xtestSize, double xtrain[xtrainSize][w], double xtest[xtestSize][w], double* ytrain);

/**
 * Funcao paralela que recebe um w, o tamanho de xtrain, o tamanho de xtest, xtrain, xtest e ytrain e retorna o array ytest
 */
double* knnParallel(int w, int k, int xtrainSize, int xtestSize, double xtrain[xtrainSize][w], double xtest[xtestSize][w], double* ytrain, int num_threads);
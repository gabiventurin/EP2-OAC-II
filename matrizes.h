/**
 * Funcao para criar a matriz sequencialmente
 * 
 * Recebe um int n, um int h, um int w, um array de doubles e um array com w colunas para alocar o resultado
 */
void createMatriz(int n, int h, int w, double* array, double result[][w]);

/**
 * Funcao para criar a matriz paralelamente
 * 
 * Recebe um int n, um int h, um int w, um array de doubles, um array com w colunas para alocar o resultado
 * e um int nThreads para determinar o número de threads utilizado
 */
void createMatrizParallel(int n, int h, int w, double* array, double result[][w], int nThreads);

/**
 * Funcao que calcula ytrain
 * 
 * Recebe um int n, um int h, um int w, o array de xtrain e onde deve ser colocado ytrain
 */
void createYtrain(int n, int h, int w, int ytrainSize, double* xtrain, double* ytrain);
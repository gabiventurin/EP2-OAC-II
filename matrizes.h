/**
 * Funcao para criar a matriz
 * 
 * Recebe um int n, um int h, um int w, um array de doubles e um array com w colunas para alocar o resultado
 */
void createMatriz(int n, int h, int w, double* array, double result[][w]);

/**
 * Funcao que calcula ytrain
 * 
 * Recebe um int n, um int h, um int w, o array de xtrain e onde deve ser colocado ytrain
 */
void createYtrain(int n, int h, int w, int ytrainSize, double* xtrain, double* ytrain);
/**
 * Function that reads a string and returns the number of '\n' in it
 */
int getNumberOfLines(char* f);

/**
 * Function that receives a file and returns a double array of all the numbers in it
 */
double* readFileAndConvertToArray(char* f);

/**
 * Function that receives a double array and its size and puts it into the file "output/Ytest.txt" 
 */
void readArrayAndConvertToFile(double* array, int arraySize);
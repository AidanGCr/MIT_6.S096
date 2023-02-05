#include <stddef.h>
#include <stdio.h> 

#include <stdlib.h> 
#include <string.h> 

// defining the structure of a matrix
typedef struct Matrix_s {
    size_t R, C;
    int* index;
} Matrix;

// for printing a line to the screen - mostly to test functions
int printLine(char* line) { 

    char* lineCopy = malloc( sizeof(line) ); 
    strcpy(lineCopy, line); 
    char *num = strtok(lineCopy, " "); 

    while (num != NULL) {
        printf("%s\n", num); 
        num = strtok(NULL, " ");
    } 

    free(lineCopy); 
    return 0; 
}

// printing characteristics of a matrix for checking if its correct
// Note: this function is inoperable in this problem 
// (see last problem for its usefulness) 
int printMatrix(Matrix matrix) { 
    
    printf("Function currently not working\n"); 
    printf("***New Matrix***\nR: %zu C: %zu\n", matrix.R, matrix.C);

    for (size_t row = 0; row < matrix.R; row++) { 
        for (size_t column = 0; column < matrix.C; column++) { 
            //printf("[%zu][%zu] = %d\n", row, column, matrix.index[row][column]);
        }
    }

    return 0; 
}

// helper to set the R and C values for a given matrix
int setRorC(char* line, char* RorC) { 

    int counter = 0; 
    char* lineCopy = malloc( sizeof(line) ); 
    strcpy(lineCopy, line); 
    char *num = strtok(lineCopy, " "); 

    while (num != NULL) { 
        if (counter == 0 && !strcmp("R", RorC)) { 
             int rowValue = atoi(num); 
             free(lineCopy);
             return rowValue;
        } else if (counter == 1 && !strcmp("C", RorC)) { 
             int columnValue = atoi(num); 
             free(lineCopy); 
             return columnValue;
        } else { 
             counter++; 
        }
        num = strtok(NULL, " "); 
    }

    free(lineCopy); 
    return 0; 
}

// helper to load a row of a matrix given a line from the input file and its matrix row index
int loadInnerMatrix(char* line, int* indexArray, size_t rowIndex, size_t columnSize) { 

    int column = 0; 
    char* lineCopy = malloc( sizeof(line) ); 
    strcpy(lineCopy, line);
    char *num = strtok(line, " ");

    while (num != NULL) { 
        indexArray[(rowIndex * columnSize) + column] = atoi(num); 
        column++; 
        num = strtok(NULL, " "); 
    }

    free(lineCopy);
    return 0; 
}

// to load the data into a matrix using the above helper methods
// Note that in this problem the 2D array is implemented as a 1D array 
// This is because the struct houses a int *index, and not an int **index  
int loadMatrices(Matrix* matrix1, Matrix* matrix2, FILE* file) { 

    size_t lineCounter = 1; 
    int numOfChars = (1000*4) + 999;
    char *line = malloc( numOfChars * sizeof(char) );

    while (fgets(line, numOfChars, file)) { 
        if (lineCounter == 1) { 
            (*matrix1).R = setRorC(line, "R"); 
            (*matrix1).C = setRorC(line, "C");
            (*matrix1).index = malloc( ((*matrix1).R * (*matrix1).C) * sizeof(int) ); 
            lineCounter++; 
        } else if (lineCounter > 1 && lineCounter < (*matrix1).R + 2) { 
            size_t rowIndex = lineCounter - 2;
            loadInnerMatrix(line, (*matrix1).index, rowIndex, (*matrix1).C);
            lineCounter++; 
        } else if (lineCounter == (*matrix1).R + 2) { 
            (*matrix2).R = setRorC(line, "R"); 
            (*matrix2).C = setRorC(line, "C");
            (*matrix2).index = malloc( ((*matrix2).R * (*matrix2).C) * sizeof(int)); 
            lineCounter++; 
        } else if (lineCounter > (*matrix1).R + 2) { 
            size_t rowIndex = lineCounter - ((*matrix1).R + 3);
            loadInnerMatrix(line, (*matrix2).index, rowIndex, (*matrix2).C); 
            lineCounter++; 
        }
    }

    free(line); 
    return 0; 

}

// check matrices can be multiplied
int canMultiply(Matrix matrix1, Matrix matrix2) { 
    return (matrix2.R == matrix1.C || matrix1.R == matrix2.C); 

    //remove - for testing
    printf("matrices cannot be multiplied"); 
}

int dotProduct(Matrix* matrix1, Matrix* matrix2, Matrix* product) { 

    // first matrix input is parsed by row first, second matrix input is parsed by column first
    for (size_t counter1 = 0; counter1 < (*matrix1).R; counter1++) { 
        for (size_t counter2 = 0; counter2 < (*matrix2).C; counter2++) { 
            int savedOutput = 0; 
            for (size_t counter3 = 0; counter3 < (*matrix1).C; counter3++) { 
                savedOutput += matrix1->index[(counter1 * matrix1->C) + counter3] * matrix2->index[(counter3 * matrix2->C) + counter2];
            }
            product->index[(counter1 * product->C) + counter2] = savedOutput; 
        }
    }

    return 0; 

}

// multiply two matrices and place the output in the product matrix
int multiplyMatrices(Matrix* matrix1, Matrix* matrix2, Matrix* product){ 

    product->R = matrix1->R; 
    product->C = matrix2->C;

    // now that the product R and C are defined, 
    // I'll initalize the product index array here
    product->index = malloc( (product->R * product->C) * sizeof(int) ); 
    
    // now we can do the dot product like before
    dotProduct(matrix1, matrix2, product); 

    return 0; 

}

int main(int argc, char** argv) { 

    //opening the input files and output files in a loop
    for (int counter = 1; counter < argc; counter++) { 

        FILE *inFile = fopen(argv[counter], "r");
        
        char *suffix = ".out";
        char *outFileName = malloc(strlen(suffix) + strlen(argv[counter]));   
        strcpy(outFileName, argv[counter]);
        strcat(outFileName, suffix); 
        FILE *outFile = fopen(outFileName, "w");
        
        // building matricies
        Matrix *matrix1; 
        Matrix *matrix2; 
        Matrix *product; 
        loadMatrices(matrix1, matrix2, inFile);   

        //check if matrices can be multiplied and multiply them
        if (canMultiply(*matrix1, *matrix2)) { 
            multiplyMatrices(matrix1, matrix2, product); 
        } else { 
            (*product).R = 0; 
            (*product).C = 0; 
        }

        // write the output to the output file
        fprintf(outFile, "%zu %zu", product->R, product->C); 
        for (size_t row = 0; row < product->R; row++) { 
            fprintf(outFile, "\n"); 
            for (size_t column = 0; column < product->C; column++) { 
                if (column == product->C - 1) { 
                    fprintf(outFile, "%d", product->index[(row * product->C) + column]);
                } else {
                    fprintf(outFile, "%d", product->index[(row * product->C) + column]); 
                } 
            }
        }

        // close files and free memory
        fclose(inFile); 
        fclose(outFile); 
        free(outFileName);
        free(matrix1->index); 
        free(matrix2->index); 
        free(matrix1); 
        free(matrix2); 
        free(product); 
    }

    return 0; 
}


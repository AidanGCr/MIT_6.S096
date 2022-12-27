#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

union float_bits {
    float f;
    unsigned int bits;
};

// print_hex( 5.Of ) outputs "The float looks like Ox4OaOOOOO in hex."
void print_hex( float f) {

    union float_bits t;
    t.f = f;
    printf( "The float looks like Ox%x in hex.\n", t.bits );

}

// return the binary version of the mantissa 
char* get_bin(unsigned int n) { 

    char *bin_value = malloc( 23 * sizeof(char) ); 

    int counter = 0; 
    unsigned int i;
    for (i = 1 << 22; i > 0; i = i /2) { 
            if (n & i) { 
                bin_value[counter] = '1'; 
                counter++; 
            } else { 
                bin_value[counter] = '0'; 
                counter++; 
            }
    }

    return bin_value; 

}

// print the proper formating to the screen for each input float
int get_format(union float_bits input, FILE* outFile) { 

    // set the values for the various parts of the floating point using bitwise operations
    unsigned int sign = input.bits >> 31; 
    //printf("Sign: %d\n", sign);

    unsigned int exponent = (input.bits << 1) >> 24;
    //printf("Exponent: %d\n", exponent);

    unsigned int mantissa = (input.bits << 9) >> 9;
    //printf("Mantissa: %d\n", mantissa);

    // get the binary version of the mantissa
    char *binMantissa = get_bin(mantissa); 
    //printf("Binary Mantissa: %s\n", binMantissa);

    // format the output 
    if (sign) { 
        fprintf(outFile, "-1.%s * 2^%d\n", binMantissa, (exponent - 127)); 
    } else { 
        fprintf(outFile, "1.%s * 2^%d\n", binMantissa, (exponent - 127)); 
    } 

    free(binMantissa); 

    return 0; 
}

int main(int argc, char** argv) { 

    // open the given input file and read it in
    // write the output to an output file
    // note that the first line of every file seems to be skipped in the example outputs

    for (int counter = 1; counter < argc; counter++) { 

        //opening input file and output file
        FILE *inFile = fopen(argv[counter], "r");
        char *suffix = ".out";
        char *outFileName = malloc(strlen(suffix) + strlen(argv[counter]));   
        strcpy(outFileName, argv[counter]);
        strcat(outFileName, suffix); 
        FILE *outFile = fopen(outFileName, "w");

        // reading input file in a loop and output to the outFile
        union float_bits currentData; 

        while (fscanf(inFile, "%f", &currentData.f) == 1 && !feof(inFile)) { 
            get_format(currentData, outFile); 
        }

        fclose(inFile); 
        fclose(outFile); 
        free(outFileName); 
    }

    return 0; 
}
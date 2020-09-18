/* Program to generate a key from supplied set of symbols in a space-separated file.
 * Authors:
 * Koustuv Kanungo, PhD18007
 * Reshan Faraz,    PhD19006
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./keygen number_of_symbols\n");
        exit(1);
    }

    int i, j, temp, *code_set;
    int total_tuples = 0, num_symbols = atoi(argv[1]);
    FILE *fp;

    // total number of possible tuples,
    // assuming substitution of 2 characters at a time
    total_tuples = num_symbols * num_symbols;
    code_set = (int *) malloc(total_tuples * sizeof(int));
    fp = fopen("./monokey", "w"); // file to store the key
    if (fp == NULL) {
        printf("Error in opening file.\n");
        exit(2);
    }

    for (i = 0; i < total_tuples; i++) {
        code_set[i] = i;
    }

    // Fisher-Yates shuffle algorithm
    srand(time(NULL)); 
    for (i = total_tuples - 1 ; i > 0; i--) {
        j = rand() % (i + 1); 
        temp = code_set[i];
        code_set[i] = code_set[j];
        code_set[j] = temp;
    }

    for (i = 0; i < total_tuples; i++) {
        fprintf(fp, "%d ", code_set[i]);
    }

    fclose(fp);
    free(code_set);

    return 0;
}

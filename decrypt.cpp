/* Program to decrypt ciphertexts given in a newline-separated file.
 * Authors:
 * Koustuv Kanungo, PhD18007
 * Reshan Faraz,    PhD19006
 */
#include <iostream>
#include <cstdlib>

int main(int argc, const char * argv[]) {
    if (argc < 4) {
        printf("Usage: ./decrypt set_of_symbols list_of_ciphertexts key_file\n");
        exit(1);
    }

    FILE *fp1, *fp2, *fp3, *fp4;
    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    fp3 = fopen(argv[3], "r");
    fp4 = fopen("./decoded_text", "w");
    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL) {
        printf("Error in opening specified files.\n");
        exit(2);
    }

    char symbol_set[254], c, c1, c2, key_table[1000], decrypt_key[1000];
    int i = 0, j = 0, k = 0;

    // get the symbols
    do {
        i = fscanf(fp1, "%c", &c);
        if (c != ' ' && c != '\n') {
            symbol_set[j] = c;
            j++;
        }
    } while (i == 1);

    // get the key
    do {
        i = fscanf(fp3, "%c", &c);
        if (c != ' ' && c != '\n') {
            key_table[k] = atoi(&c);
            k++;
        }
    } while (i == 1);

    // reverse the key for decryption
    for (i = 0; i < k; i++) {
        decrypt_key[key_table[i]] = i;
    }

    // generate the substitution tuples
    char *symbol_tuples = (char *) malloc(j * j * sizeof(char));
    for (i = 0; i < j * j; i++) {
        symbol_tuples[i * 2] = symbol_set[i / 3];
        symbol_tuples[i * 2 + 1] = symbol_set[i % 3];
    }

    // substitute the tuples by using the decryption key
    while (1) {
        i = fscanf(fp2, "%c", &c);
        if (i != 1)
            break;
        else if (c == ' ' || c == '\n') {
            fprintf(fp4, "%c", c);
        }
        else {
            c1 = c;
            fscanf(fp2, "%c", &c2);
            for (k = 0; k < j * j; k++) {
                if (symbol_tuples[k * 2] == c1 && symbol_tuples[k * 2 + 1] == c2) {
                    fprintf(fp4, "%c%c", symbol_tuples[decrypt_key[k] * 2], symbol_tuples[decrypt_key[k] * 2 + 1]);
                }
            }
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}

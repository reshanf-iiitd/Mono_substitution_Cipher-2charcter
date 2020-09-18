/* Program to brute force the key to a monoalphabetic substitution cipher, with
 * the ciphertexts provided in a newline-separated file.
 * Authors:
 * Koustuv Kanungo, PhD18007
 * Reshan Faraz,    PhD19006
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    if (argc < 3) {
        printf("Usage: ./codebreaker set_of_symbols list_of_ciphertexts\n");
        exit(1);
    }

    FILE *fp1, *fp2, *fp3, *fp4;
    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    if (fp1 == NULL || fp2 == NULL) {
        printf("Error in opening specified files.\n");
        exit(2);
    }

    char symbol_set[254], c, c1, c2, decrypt_key[1000];
    int i = 0, j = 0, k = 0, pattern_broken = 0, prev_val = 9999;

    // get the symbols
    do {
        i = fscanf(fp1, "%c", &c);
        if (c != ' ' && c != '\n') {
            symbol_set[j] = c;
            j++;
        }
    } while (i == 1);

    // generate the substitution tuples
    char *symbol_tuples = (char *) malloc(j * j * sizeof(char));
    for (i = 0; i < j * j; i++) {
        symbol_tuples[i * 2] = symbol_set[i / 3];
        symbol_tuples[i * 2 + 1] = symbol_set[i % 3];
    }

    for (i = 0; i < j * j; i++) {
        decrypt_key[i] = i;
    }

    while (1) {
        next_permutation(decrypt_key, decrypt_key + j * j);
        pattern_broken = 0;
        // substitute the tuples by using the decryption key
        while (1) {
            i = fscanf(fp2, "%c", &c);
            if (i != 1)
                break;
            else if (c == ' ') {
                continue;
            }
            else if (c == '\n') {
                prev_val = 9999;
            }
            else {
                c1 = c;
                fscanf(fp2, "%c", &c2);
                for (k = 0; k < j * j; k++) {
                    if (symbol_tuples[k * 2] == c1 && symbol_tuples[k * 2 + 1] == c2) {
                        if (prev_val < decrypt_key[k]) {
                            pattern_broken = 1;
                        }
                        else {
                            prev_val = decrypt_key[k];
                        }
                    }
                }
            }
        }

        if (!pattern_broken) {
            break;
        }
        else {
            fseek(fp2, 0, SEEK_SET);
        }
    }

    printf("Key is:\n");
    for (i = 0; i < j * j; i++) {
        printf("%d ", decrypt_key[i]);
    }
    printf("\n");

    fclose(fp1);
    fclose(fp2);

    return 0;
}

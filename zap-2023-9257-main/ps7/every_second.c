#include <stdio.h>

int findBorder(char *word1, char *word2);
void checkFile(const char *Ifilename, const char *Ofilename);

int main(int argumentSize, char *argumentUse[]) {

    if (argumentSize != 3) {
        printf("Usage: %s <Ifilename> <Ofilename>\n", argumentUse[0]);
        return -1;
    } else {

        char *Ifilename = argumentUse[1];
        char *Ofilename = argumentUse[2];
        checkFile(Ifilename, Ofilename);

        return 0;
    }
}

int findBorder(char *word1, char *word2) {
    while (*word1 != '\0' && *word2 != '\0') {
        if (*word1 != *word2) {
            return 0;
        }
        word1++;
        word2++;
    }

    return *word1 == '\0' && *word2 == '\0';
}

void checkFile(const char *Ifilename, const char *Ofilename) {

    FILE *txtf = fopen(Ifilename, "r");

    if (txtf == NULL) {
        printf("Unable to open the input file!\n");
        return;
    }

    FILE *txtf2 = fopen(Ofilename, "w");

    if (txtf2 == NULL) {
        printf("Unable to open the output file!\n");
        fclose(txtf);
        return;
    }

    int c, wordCount = 0, borderFound = 0, outputWord = 0;
    char words[100];

    while ((c = fgetc(txtf)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            words[wordCount] = '\0';

            if (findBorder(words, "START")) {
                borderFound = 1;
            } else if (findBorder(words, "STOP")) {
                break;
            } else if (borderFound) {
                if (outputWord) {
                    int i = 0;
                    while (words[i] != '\0') {
                        fputc(words[i], txtf2);
                        i++;
                    }
                    fputc(c, txtf2);  // include the space character
                }
                outputWord = !outputWord;
            }

            wordCount = 0;
        } else {
            words[wordCount++] = c;
        }
    }
    fclose(txtf);
    fclose(txtf2);
}
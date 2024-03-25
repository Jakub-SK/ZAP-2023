#include <stdio.h>

char lowerCase( char c );
int countananas( char *filename, int *c );

int main( int argumentSize, char *argumentUse[] ) {

    // trial and error wins again

    if ( argumentSize != 2 ) {
        printf("You're supposed to only use two arguments, like this: %s <filename>\n", argumentUse[0]);
        return -1;
    } else {
        char *filename = argumentUse[1];
        int result = 0; 
        countananas(filename, &result);
        return 0;
    }
}

char lowerCase( char c ) {
    // convert uppercase letter to lowercase
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}

int countananas( char *filename, int *c ) {
    FILE *txtf = fopen(filename, "r");

    if ( txtf == NULL ) {
        printf("Unable to open that file!\n");
        return -1;
    }

    int ananasCount = 0, ananasIndex = 0, ananasik = 0;
    const char *ananas = "ananas";

    // checks all the damn letters

    int currentChar;

    while ((currentChar = fgetc(txtf)) != EOF) {
        char lowerC = lowerCase((char)currentChar);

        if ( lowerC == ananas[ananasIndex] ) {
            ananasIndex++;

            if ( ananas[ananasIndex] == '\0' ) {
                ananasCount++;
                ananasIndex = 0;
            }
        } else if ( ananasIndex > 0 ) {
            ananasIndex = (lowerC == ananas[0]) ? 1 : 0;
        }
    }

    fclose(txtf);

    txtf = fopen(filename, "w");

    if (txtf == NULL) {
        printf("Unable to open that file!\n");
        return -1;
    }

    while ( ananasCount >= 10 ) {
        ananasCount -= 10;                 
        ananasik++;          
    }
    if ( ananasik > 0 ) {
        fputc(ananasik + '0', txtf);
    }
    fputc(ananasCount + '0', txtf);

    fclose(txtf);
    return 0;
}

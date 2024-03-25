#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <time.h>
#include <string.h>
#include <ctype.h> 


int get_word(char secret[]){
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{

        long int random = (rand() % size) + 1;
        fseek(fp, random, SEEK_SET);
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
    int i;
    char *finder;

    finder = (char *) malloc(15); 

    for (i = 0; i < strlen(secret); i++){
        finder = strchr(letters_guessed, secret[i]);
        while (finder == NULL) {
            return 0;
        }
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {

    int i, j = 0;
    char *finder;

    finder = (char *) malloc(15);

    for (i = 1; i < (strlen(secret) * 2); i++) {
        if (i % 2 != 0) {
            finder = strchr(letters_guessed, secret[j++]);
            guessed_word[i - 1] = finder != NULL ? *finder : '_';
        }
        else
            guessed_word[i - 1] = ' ';
    }
    guessed_word[i] = '\0'; 
    printf("%s", guessed_word); 
}

void get_available_letters(const char letters_guessed[], char available_letters[]) {
    int i, j = 0;
    char *finder, abcd[] = "abcdefghijklmnopqrstuvwxyz";

    finder = (char *) malloc(15);

    for (i = 0; i < strlen(abcd); i++){
        finder = strchr(letters_guessed, abcd[i]);
        if (finder != NULL)
            continue;
        else {
            available_letters[j++] = abcd[i];
        }
    }
    available_letters[j] = '\0';
    printf("%s", available_letters); 
}

void hangman(const char secret[]) {
    int i = 0, j, k = 0, ongoing = 1, attempts = 8;
    char c, hidden[15], alphabet[30], input[50] = "", output[30] = "", h_i_d_d_e_n[30] = "";

    get_word(hidden); 

    for (j = 0; j < strlen(hidden); j++)
        hidden[j] = tolower(hidden[j]);

    for (j = 1; j < strlen(hidden) * 2; j++)
        h_i_d_d_e_n[j - 1] = j % 2 == 0 ? ' ' : hidden[k++];
    h_i_d_d_e_n[j] = '\0';
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %ld letters long.", strlen(hidden));
    printf("\n\n-----------------------------------------------\n");

    while (ongoing) {
        printf("\nYou have %d guesses left.\nAvailable letters: ", attempts);
        get_available_letters(input, alphabet);
        printf("\nPlease guess a letter: ");
        scanf("%c", &c);
        while (getchar() != '\n')                      
        c = tolower(c); 

        if (!strchr(alphabet, c)) {
            printf("\nOops! You've already guessed that letter: ");
            get_guessed_word(hidden, input, output); 
            printf("\n\n-----------------------------------------------\n;
            continue;
        }
        input[i++] = c; 

        if (strchr(hidden, c)) {
            printf("\nGoog quess: ");
            get_guessed_word(hidden, input, output); 

            is_word_guessed(hidden, input);
            if (strcmp(h_i_d_d_e_n, output) == 0) {
                printf("\n\n-----------------------------------------------\n");;
                printf("\nCongratulations, you won!\n"); 
                break; 
            }
        }

        else {
            printf("\nOops! That letter is not in my word: ");
            get_guessed_word(hidden, input, output);
            attempts--; 

            if (attempts == 0) {
                printf("\n\n-----------------------------------------------\n");;
                printf("\nSorry, you ran out of guesses. The word \"%s\" was not guessed properly.\n", hidden);
                break; 
            }
        }
        printf("\n\n-----------------------------------------------\n");
    }
}
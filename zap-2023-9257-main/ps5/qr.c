#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main() {



}

void encode_char(const char character, bool bits[8]) {

    int remainder, number = character;
    
    for (int i = 7; i >= 0; i--) {
        remainder = number % 2;
        number /= 2;
        bits[i] = remainder;
    }
}

char decode_byte(const bool bits[8]) {

    int number = 2, sum = 0;

    for (int i = 7; i >= 0; i--) {
        int shift = i;
        if (i == 7 && bits[i] == 1) {
            sum += 1;
        } else if (i == 6 && bits[i] == 1) {
            sum += 2;
        } else {
            while (shift < 6) {
                number *= 2;
                shift++;
            }
            if (bits[i] == 1) {
                sum += number;
            }
            number = 2;
        }
    }
    return (char)sum;
}

void encode_string(const char string[], bool bytes[strlen(string) + 1][8]) {

    int character;
    bool bits[8];
    int count = strlen(string);
    printf("%d\n", count);

    for (int i = 0; i <= count + 1; i++) {
        if (i != count + 1) {
            character = string[i];
            encode_char(character, bits);
            for (int j = 0; j < 8; j++) {
                bytes[i][j] = bits[j];
            }
        } else {
            for (int k = 0; k < 8; k++) {
                bytes[count + 1][k] = '0';
            }
        }
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]) {
    char character;
    bool helper[8];

    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j < 8; j++) {
            helper[j] = bytes[i][j];
        }
        if (i == rows) {
            string[i] = '\0';
            break;
        }
        character = decode_byte(helper);
        string[i] = character;
    }
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8]) {
    bool helper[8];
    int i = 0, counter = 0, number = 0;

    for (int a = 0; a < offset; a++) {
        for (int m = 0; m < cols; m++) {
            if (i == rows) {
                while (m < cols) {
                    for (int n = number; n < 8 + number; n++) {
                        blocks[n][m] = 0;
                    }
                    m++;
                }
                break;
            }
            for (int j = 0; j < 8; j++) {
                helper[j] = bytes[i][j];
            }
            counter = 0;
            for (int n = number; n < 8 + number; n++) {
                blocks[n][m] = helper[counter];
                counter++;
            }
            i++;
        }
        number += 8;
    }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8]) {
    int number = 0;
    int i = 0;

    while (i != rows) {
        for (int m = 0; m < cols; m++) {
            int k = 0;
            for (int n = number; n < 8 + number; n++) {
                bytes[i][k] = blocks[n][m];
                k++;
            }
            i++;
            if (i == rows) {
                break;
            }
        }
        number += 8;
    }
}
#include "stdio.h"

#define PNG_SIGNATURE_LENGTH 8
const static int PNG_SIGNATURE[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

int main(void) {
    FILE *fp = fopen("practice.png", "rb");
    if (fp == NULL) {
        printf("Unable to open file.");
        return 1;
    }

    // Check the PNG signature
    for (int i = 0; i < PNG_SIGNATURE_LENGTH; i++) {
        if (getc(fp) != PNG_SIGNATURE[i]) {
            printf("Incorrect PNG Signature\n");
            return 1;
        }
    }
    printf("———————————————————————\n");
    printf("PNG signature validated");
    printf("\n———————————————————————");

    // read LENGTH
    printf("\nLENGTH:\n\t");
    for (int i = 0; i < 4; i++) {
        printf("%d ", getc(fp));
    }

    // read CHUNK TYPE
    printf("\nCHUNK_TYPE:\n\t");
    for (int i = 0; i < 4; i++) {
        printf("%c ", getc(fp));
    }

    // read WIDTH
    printf("\nWIDTH:\n\t");
    for (int i = 0; i < 4; i++) {
        printf("%d ", getc(fp));
    }

    // read HEIGHT
    printf("\nHEIGHT:\n\t");
    for (int i = 0; i < 4; i++) {
        printf("%d ", getc(fp));
    }

    // read BIT DEPTH
    printf("\nBIT DEPTH:\n\t");
    printf("%d ", getc(fp));

    // read COLOR TYPE
    printf("\nCOLOR TYPE:\n\t");
    printf("%d ", getc(fp));

    // read COMPRESSION METHOD
    printf("\nCOMPRESSION METHOD:\n\t");
    printf("%d ", getc(fp));

    // read FILTER METHOD
    printf("\nFILTER METHOD:\n\t");
    printf("%d ", getc(fp));

    // read INTERLACE METHOD
    printf("\nINTERLACE METHOD:\n\t");
    printf("%d ", getc(fp));

    // https://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html
    // Continue ^
    printf("\nREST:\n");
    int byte;
    while ((byte = getc(fp)) != EOF) {
        printf("%d ", byte);
    }

    fclose(fp);
    return 0;
}

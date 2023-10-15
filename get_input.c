#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float get_float_input(char* prompt) {
    float input;
    printf("%s", prompt);
    scanf("%f", &input);
    return input;
}

int get_int_input(char* prompt) {
    int input;
    char c;

    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &input) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return input;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

char get_char_input(char* prompt) {
    char input;
    char c;

    while (1) {
        printf("%s", prompt);
        if (scanf(" %c", &input) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return input;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

char* get_string_input(char* prompt) {
    char buffer[100];
    char* input;
    char c;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            input = malloc(strlen(buffer) + 1);
            strcpy(input, buffer);
            return input;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "myInput.h"

int inputInt(int min, int max) {

    char numberStr[12];

    while (1) {

        fgets(numberStr, 11, stdin);

        numberStr[strlen(numberStr) - 1] = 0;

        int result = atoi(numberStr);

        if (result >= min && result <= max) {

            return result;
        }
        else printf("Please, enter a number between %d and %d:\n", min, max);
    }
}

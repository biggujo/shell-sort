#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "myInput.h"

// Input an integer in proper range
int inputInt(int *numberi, int min, int max) {
    if (min < INT_MIN || max > INT_MAX) {
        printf("ERR: There may be a type overflow!\n");
        printf("Please, change \"min\" and \"max\" to be in range between INT_MIN and INT_MAX\n");
        return -1;
    }
    char numberStr[19];
    int result;
    while (1) {
        // Input number and clear buffer
        fflush(stdin);
        fgets(&numberStr[0], 11, stdin);

        if (numberStr[0] == '\n') return 0;

        // Strip "\n" (set "\0")
        numberStr[strlen(numberStr) - 1] = 0;

        // If zero and it is allowed
        if (numberStr[0] == '0' && numberStr[1] == '\0' && 0 >= min && 0 <= max) {
            fflush(stdin);

            // Return OK
            *numberi = 0;
            return 1;
        }

            // If not zero
        else {
            if (isStrInteger(&numberStr[0])) {
                result = (int) strtol(&numberStr[0], NULL, 10);// Convert to a number
            }
            else result = 1;
            // If number meet requirements
            if (result != 0 && result >= min && result <= max) {
                fflush(stdin);

                // Return OK
                *numberi = (int) result;
                return 1;
            }

                // If error
            else {

                // Print error
                printf("Please, enter an integer from %d to %d:\n", min, max);
            }
        }
    }
}

// Check whether the number is an integer
// Return: 1 - OK, 0 - Not OK
int isStrInteger(const char *num) {
    size_t i;
    size_t len = strlen(num);

    // Check first character
    if (0 == ('-' == num[0] || '+' == num[0] || isdigit(num[0]))) {

        // Return not OK
        return 0;
    }
    for (i = 1; i < len; i++) {

        if (!isdigit(num[i])) {
            return 0; // If character is not a digit
        }
    }
    // If all characters is digits
    return 1;
}
/* Norris Spencer
 * Leah Ruisenor
 *
 * TCSS 422
 * Winter 2018
 * Home Work 1: mash.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CHARS 255


int main(void) {

    char command[MAX_CHARS];    // max of 255 per command
    int i = 1;
    int c;


    // read in the comand line
    while (i < 5) {

        if (i < 4) {
            printf("mash-%d>", i);
        } else {
            printf("file>");
        }

        int j = 0;

        while( (c = fgetc(stdin) != '\n') ) {
            command[j++] = c;
        }
        command[j] = '\0';     // get next command
        i++;
    }

    return 0;
}

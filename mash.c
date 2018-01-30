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

typedef struct {
 char * c1;
 char * c2;
 char * c3;
 char * theFile;
} myargs;


void mash( char cmnd1[], char cmnd2[], char cmnd3[], char file[] ) {

/*
    p1 = fork();
    if (p1 == 0) // child
        if (p1 > 0) // parent

    p2 = fork();
    if (p2 == 0) // child
        if (p2 > 0)

    p3 = fork();
    if (p3 == 0) // child
        if (p3 > 0)

    wait(..)
*/

// print startments

    // printf("-----LAUNCH CMD %d: %s", i, theCommand);

    // printf("-"); // gonna have to be in a loop

    // printf("CMD%d:[SHELL %d] STATUS CODE=-1\n", i);

    // printf("Result took:%d", timeMS);

    // printf("Done waiting on children: %d %d %d\n", p1, p2, p3);

    // printf("mash-%d>", i);

}


int main(void) {

    myargs a;

    char command[MAX_CHARS];    // max of 255 per command
    int i = 1;
    char ch;

    /***********************************
     * I think we should make a struct *
     * for the args and then pass them *
     * to the mash function.           *
     ***********************************/

    // read in the comand line
    while (i < 5) {

        if (i < 4) {
            printf("mash-%d>", i);
        } else {
            printf("file>");
        }

        int j = 0;

        while( (ch = fgetc(stdin) != '\n') ) {
            command[j++] = ch;
            // add to struct here
        }
        command[j] = '\0';     // get next command
        i++;

        // testing adding them to the struct here
        a.c1 = "one";
        a.c2 = "two";
        a.c3 = "three";
        a.theFile = "file";
    }

    printf("\nTesting:\n");
    printf("command 1: %s\n", a.c1);
    printf("command 2: %s\n", a.c2);
    printf("command 3: %s\n", a.c3);
    printf("the file name: %s\n", a.theFile);

    // // pass the args to the mash function call
    // mash(a);
    // mash(c1, c2, c3, theFile);

    return 0;
}

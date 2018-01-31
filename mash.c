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

// typedef struct {
//     char * c1;
//     char * c2;
//     char * c3;
//     char * theFile;
// } myArg;

void mash(char cmnd1[], char cmnd2[], char cmnd3[], char file[]) {

    int p1;
    int p2;
    int p3;

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

    for (int i = 0; i < 80; i++) {
        printf("-"); // gonna have to be in a loop
    }
    printf("\n");

    // printf("CMD%d:[SHELL %d] STATUS CODE=-1\n", i);

    // printf("Result took:%d", timeMS);

    //printf("Done waiting on children: %d %d %d\n", p1, p2, p3);

}


int main(int argc, char *argv[]) {

    //myArg a;

    char firstCommand[MAX_CHARS];
    char secondCommand[MAX_CHARS];
    char thirdCommand[MAX_CHARS];
    char fileIn[MAX_CHARS];
    char charIn;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    printf("mash-1>");
    while ((charIn = fgetc(stdin)) != '\n') {
        firstCommand[i++] = charIn;
    }
    firstCommand[i] = '\0';

    printf("mash-2>");
    while ((charIn = fgetc(stdin)) != '\n') {
        secondCommand[j++] = charIn;
    }
    secondCommand[j] = '\0';

    printf("mash-3>");
    while ((charIn = fgetc(stdin)) != '\n') {
        thirdCommand[k++] = charIn;
    }
    thirdCommand[k] = '\0';

    printf("file>");
    while ((charIn = fgetc(stdin)) != '\n') {
        fileIn[l++] = charIn;
    }
    fileIn[l] = '\0';

    // pass the args to the mash function call
    mash(firstCommand, secondCommand, thirdCommand, fileIn);

    return 0;
}

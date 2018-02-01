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

#define MAX_CHARS 255   // no more than 255 characters per line
#define MAX_ARGS 6      // no more than 5 args plus Null terminating char

// typedef struct {
//     char * c1;
//     char * c2;
//     char * c3;
//     char * theFile;
// } myArg;

void mash(char *cmnd1, char *cmnd2, char *cmnd3, char *file) {

    int p1;
    int p2;
    int p3;

    int i = 0;
    int k = 0;
    int j = 0;

    char *stf = strdup(file);   // strdup() returns a pointer to a new string which is a duplicate of the string s.
                                // source: https://linux.die.net/man/3/strndup
    char *tempArgs1[MAX_ARGS];
    char *tempArgs2[MAX_ARGS];
    char *tempArgs3[MAX_ARGS];

    char *tempChars1 = strtok(cmnd1, " ");  // source: http://www.cplusplus.com/reference/cstring/strtok/
    char *tempChars2 = strtok(cmnd2, " ");
    char *tempChars3 = strtok(cmnd3, " ");

    // ////////////////////
    //     while(tempChars2 != '\0') {
    //         tempArgs2[j] = tempChars2;
    //         tempChars2 = strtok('\0', " ");
    //         i++;
    //     }
    //     tempArgs2[j] = stf;
    //     tempArgs2[j + 1] = '\0';
    //     execvp(tempArgs2[0], tempArgs2);
    //
    // ///////////////////
    //     while(tempChars3 != '\0') {
    //         tempArgs3[k] = tempChars3;
    //         tempChars3 = strtok('\0', " ");
    //         i++;
    //     }
    //     tempArgs3[k] = stf;
    //     tempArgs3[k + 1] = '\0';
    //     execvp(tempArgs3[0], tempArgs3);


    p1 = fork();

    if (p1 == 0) {  // child

        // doing the stuff
        while(tempChars1 != '\0') {
            tempArgs1[i] = tempChars1;
            tempChars1 = strtok('\0', " ");
            i++;
        }
        tempArgs1[i] = stf;
        tempArgs1[i + 1] = '\0';          // have to add Null terminating char
        execvp(tempArgs1[0], tempArgs1); // source: https://stackoverflow.com/questions/27541910/how-to-use-execvp
    }

    if (p1 > 0) {   // parent

        p2 = fork();

        if (p2 == 0) {  // child

            // do the stuff

        }

        if (p2 > 0) {

            p3 = fork();

            if (p3 == 0) {  // child

                // do the stuff

            }

            if (p3 > 0) {
                wait(NULL); //source: https://stackoverflow.com/questions/45666076/what-does-waitnull-do-in-this-case-and-what-is-the-output-of-the-program
            }
            wait(NULL);
        }
        wait(NULL);
    }

    printf("Done waiting on children: %d %d %d\n", p1, p2, p3);


    // Print startments

    // printf("-----LAUNCH CMD %d: %s", i, theCommand);

    // for (int i = 0; i < 80; i++) {
    //     printf("-"); // gonna have to be in a loop
    // }
    // printf("\n");

    // printf("CMD%d:[SHELL %d] STATUS CODE=-1\n", i);

    // printf("Result took:%d", timeMS);
    
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

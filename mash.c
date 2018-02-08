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
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHARS 255   // no more than 255 characters per line
#define MAX_ARGS 6      // no more than 5 args plus Null terminating char
#define REMAIN_PRINT_PROMPT 61

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

    char *stf = strdup(file);   // strdup() returns a pointer to a new string
    // which is a duplicate of the string s.
    // source: https://linux.die.net/man/3/strndup
    char *tempArgs1[MAX_ARGS];
    char *tempArgs2[MAX_ARGS];
    char *tempArgs3[MAX_ARGS];

    // source: http://www.cplusplus.com/reference/cstring/strtok/
    char *tempChars1 = strtok(cmnd1, " ");
    char *tempChars2 = strtok(cmnd2, " ");
    char *tempChars3 = strtok(cmnd3, " ");


    p1 = fork();
    if (p1 == 0) {  // child
        //printf("\n-----LAUNCH CMD 1: ");
        while(tempChars1 != NULL) {
            tempArgs1[i] = tempChars1;
            tempChars1 = strtok(NULL, " ");
            //printf("%s", tempArgs1[i]);
            i++;
        }
        //printf("-----LAUNCH CMD 1: %s\n", *tempArgs1);
        //int remainDash = (REMAIN_PRINT_PROMPT - i);
        //printf("Dashes to print 1: %i\n", remainDash);
        tempArgs1[i] = stf;
        tempArgs1[i + 1] = NULL;          // have to add Null terminating char
        execvp(tempArgs1[0], tempArgs1); // source: https://stackoverflow.com/questions/27541910/how-to-use-execvp
    }

    if (p1 > 0) {   // correct 1 // parent
        p2 = fork();

        if (p2 == 0) { // correct 2  // child
            //printf("\n-----LAUNCH CMD 2: ");
            while(tempChars2 != NULL) {
                tempArgs2[j] = tempChars2;
                tempChars2 = strtok(NULL, " ");
                //printf("%s", tempArgs2[j]);
                j++; //here
            }
            //int remainDash = (REMAIN_PRINT_PROMPT - i);
            //printf("Dashes to print 2: %i\n", remainDash);
            tempArgs2[j] = stf;
            tempArgs2[j + 1] = NULL;
            execvp(tempArgs2[0], tempArgs2);
        } // correct 2

        if (p2 > 0) { // correct 3
            p3 = fork();

            if (p3 == 0) { // correct 4  // child
                while(tempChars3 != NULL) {
                    tempArgs3[k] = tempChars3;
                    tempChars3 = strtok(NULL, " ");
                    //printf("\n-----LAUNCH CMD 3: %s", tempArgs3[k]);
                    k++; //here
                }
                //printf("-----LAUNCH CMD 3: %s\n", *tempArgs3);
                //int remainDash = (REMAIN_PRINT_PROMPT - i);
                //printf("Dashes to print 3: %i\n", remainDash);
                tempArgs3[k] = stf;
                tempArgs3[k + 1] = NULL;
                execvp(tempArgs3[0], tempArgs3);
            } // correct 4

            if (p3 > 0) { // correct 5
                wait(NULL); //source: https://stackoverflow.com/questions/45666076/what-does-waitnull-do-in-this-case-and-what-is-the-output-of-the-program
            } // correct 5
            wait(NULL);
        } // correct 3
        wait(NULL);
    } // correct 1
    printf("\n");
    for (int l = 0; l < 8;l++) {
        printf("----------");
    }
    if (p1 != 0 && p2 != 0 && p3 != 0) {
        printf("\nDone waiting on children: %d %d %d\n", p1, p2, p3);
    }
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

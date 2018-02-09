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
#include <time.h>

#define MAX_CHARS 255   // no more than 255 characters per line
#define MAX_ARGS 6      // no more than 5 args plus Null terminating char
#define REMAIN_PRINT_PROMPT 61

void mash(char *cmnd1, char *cmnd2, char *cmnd3, char *file) {

    int p1;
    int p2;
    int p3;

    int i = 0;
    int k = 0;
    int j = 0;

    char tempCmnd1[MAX_CHARS];
    char tempCmnd2[MAX_CHARS];
    char tempCmnd3[MAX_CHARS];
    strcpy(tempCmnd1, cmnd1);
    strcpy(tempCmnd2, cmnd2);
    strcpy(tempCmnd3, cmnd3);
    char *stf = strdup(file);   // file to count
    // strdup() returns a pointer to a new string
    // which is a duplicate of the string s.;
    // source: https://linux.die.net/man/3/strndup
    char *tempArgs1[MAX_ARGS];
    char *tempArgs2[MAX_ARGS];
    char *tempArgs3[MAX_ARGS];

    // source: http://www.cplusplus.com/reference/cstring/strtok/
    char *tempChars1 = strtok(cmnd1, " ");
    char *tempChars2 = strtok(cmnd2, " ");
    char *tempChars3 = strtok(cmnd3, " ");

    p1 = fork();
    if (p1 < 0) { // first fork failed
        fprintf(stderr, "fork failed\n");
        exit(1); // exit
    }
    else if (p1 == 0) {  // child
        if (cmnd1[0] != 0) {
            while(tempChars1 != NULL) {
                tempArgs1[i] = tempChars1;
                tempChars1 = strtok(NULL, " ");
                i++;
            }
            printf("-----LAUNCH CMD 1: %s", tempCmnd1);
            int dashAmt1 = (REMAIN_PRINT_PROMPT - strlen(tempCmnd1));
            while (dashAmt1 != 0) {
                printf("-");
                dashAmt1--;
            }
            printf("\n");
            tempArgs1[i] = stf;              // source: https://stackoverflow.com/questions/27541910/how-to-use-execvp
            tempArgs1[i + 1] = NULL;        // marks the end of the array
            if (execvp(tempArgs1[0], tempArgs1) == -1) {
                printf("CMD1:[SHELL 1] STATUS CODE = -1\n");
            }

        }
    }
    if (p1 > 0) {   // parent
        p2 = fork();
        if (p2 < 0) { // second fork failed
            fprintf(stderr, "fork failed\n");
            exit(1); // exit
        }
        else if (p2 == 0) {  // child
            if (cmnd2[0] != 0) {
                while(tempChars2 != NULL) {
                    tempArgs2[j] = tempChars2;
                    tempChars2 = strtok(NULL, " ");
                    j++;
                }
                printf("-----LAUNCH CMD 2: %s", tempCmnd2);
                int dashAmt2 = (REMAIN_PRINT_PROMPT - strlen(tempCmnd2));
                while (dashAmt2 != 0) {
                    printf("-");
                    dashAmt2--;
                }
                printf("\n");
                tempArgs2[j] = stf;
                tempArgs2[j + 1] = NULL; // marks the end of the array

                if (execvp(tempArgs2[0], tempArgs2) == -1) {
                    printf("CMD2:[SHELL 2] STATUS CODE = -1\n");
                }
            }
        }
        if (p2 > 0) {
            p3 = fork();
            if (p3 < 0) { // third fork failed
                fprintf(stderr, "fork failed\n");
                exit(1); // exit
            }
            else if (p3 == 0) {  // child
                if (cmnd3[0] != 0) {
                    while(tempChars3 != NULL) {
                        tempArgs3[k] = tempChars3;
                        tempChars3 = strtok(NULL, " ");
                        k++;
                    }
                    printf("-----LAUNCH CMD 3: %s", tempCmnd3);
                    int dashAmt3 = (REMAIN_PRINT_PROMPT - strlen(tempCmnd3));
                    while (dashAmt3 != 0) {
                        printf("-");
                        dashAmt3--;
                    }
                    printf("\n");
                    tempArgs3[k] = stf;
                    tempArgs3[k + 1] = NULL;        // marks the end of the array

                    if (execvp(tempArgs3[0], tempArgs3) == -1) {
                        printf("CMD3:[SHELL 3] STATUS CODE = -1\n");
                    }
                }
            }
            if (p3 > 0) {
                wait(NULL);
            }
            wait(NULL);
        }
        wait(NULL);
    }
    if (p1 != 0 && p2 != 0 && p3 != 0) {
        for (int l = 0; l < 8; l++) {
            printf("----------");
        }
        printf("\n");
        printf("Done waiting on children: %d %d %d\n", p1, p2, p3);
    }
}

int main(int argc, char *argv[]) {

    char firstCommand[MAX_CHARS];
    char secondCommand[MAX_CHARS];
    char thirdCommand[MAX_CHARS];
    char fileIn[MAX_CHARS];
    char charIn;
    firstCommand[0] = 0;
    secondCommand[0] = 0;
    thirdCommand[0]= 0;
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

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
    char *stf = strdup(file);   // strdup() returns a pointer to a new string
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
    if (p1 == 0) {  // child
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
        tempArgs1[i] = stf;
        tempArgs1[i + 1] = '\0';         // have to add Null terminating char
        execvp(tempArgs1[0], tempArgs1); // source: https://stackoverflow.com/questions/27541910/how-to-use-execvp
    } else if (p1 > 0) {   // parent
		p2 = fork();
	      if (p2 == 0) {  // child
	          while(tempChars2 != NULL) {
	              tempArgs2[j] = tempChars2;
	              tempChars2 = strtok(NULL, " ");
	              j++;
	          }
	          printf("-----LAUNCH CMD 2: %s\n", tempCmnd2);
            int dashAmt2 = (REMAIN_PRINT_PROMPT - strlen(tempCmnd2));
            while (dashAmt2 != 0) {
                printf("-");
            dashAmt2--;
            }
	          tempArgs2[j] = stf;
	          tempArgs2[j + 1] = '\0';
	          execvp(tempArgs2[0], tempArgs2);
	      } else if (p2 > 0) {
	          p3 = fork();
	          if (p3 == 0) {  // child
	              while(tempChars3 != NULL) {
	                  tempArgs3[k] = tempChars3;
	                  tempChars3 = strtok(NULL, " ");
	                  k++;
	              }
	              printf("-----LAUNCH CMD 3: %s\n", tempCmnd3);
                int dashAmt3 = (REMAIN_PRINT_PROMPT - strlen(tempCmnd3));
                while (dashAmt3 != 0) {
                    printf("-");
                dashAmt3--;
                }
	              tempArgs3[k] = stf;
	              tempArgs3[k + 1] = '\0';
	              execvp(tempArgs3[0], tempArgs3);
	          } else if (p3 > 0) {
	              wait(NULL); //source: https://stackoverflow.com/questions/45666076/what-does-waitnull-do-in-this-case-and-what-is-the-output-of-the-program
	          }
	          wait(NULL);
            for (int l = 0; l < 8;l++) {
                printf("----------");
            }
	      }
	      wait(NULL);
	  }
    for (int l = 0; l < 8;l++) {
        printf("----------");
    }
    printf("\nDone waiting on children: %d %d %d\n", p1, p2, p3);
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

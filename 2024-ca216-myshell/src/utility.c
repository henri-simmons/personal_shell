/*
name: Henri Simmons-Hayden
student number: 22422504
I acknowledge the DCU Academic Integrity Policy
*/

// formatted with https://codebeautify.org/c-formatter-beautifier for improved readability

#include <stdio.h>

#include "myshell.h"

#include <unistd.h>

#include <stdlib.h>

#include <dirent.h>

#include <sys/wait.h>

// prompt design to run when shell is launched (purely aesthetic)
void printShellPrompt() {
    printf("############################################################\n");
    printf("#                                                          #\n");
    printf("#                    Welcome to My Shell                   #\n");
    printf("#                    Author: Henri Simmons                 #\n");
    printf("#                                                          #\n");
    printf("############################################################\n");
    printf("\n");
}

// command to change directories
int cd(char * directory) {
    // report current directory
    if (directory == NULL) {
        return 0;
    }

    // error if directory not found
    if (chdir(directory) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}

// command to print working directory
void pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd); // Print current working directory
    } else {
        perror("pwd"); // Print error message if getcwd fails
    }
}

// calls system command to clear screen
void clr() {
    system("clear");
}

// function for dir command to list contents of directory
void dir(char * directory) {
    if (directory == NULL) {
        system("ls -al");
    } else {
        char command[1024];
        sprintf(command, "ls -al %s", directory);

        // Execute the command using system call
        system(command);
    }
}

// function for environ command to list environment strings
void printEnviron() {
    // pointer to the environment variables
    extern char ** environ;

    // loop through and print all environment strings
    for (char ** env = environ;* env != NULL; env++) {
        printf("%s\n", * env);
    }
}

// function for echo command to output a message to the display
void echo(char * message) {
    printf("%s\n", message);
}

// function for pause command to pause operation of shell until
// enter is pressed
void pauseShell() {
    printf("Press Enter to resume...\n");
    while (getchar() != '\n');
}
/*
name: Henri Simmons-Hayden
student number: 22422504
I acknowledge the DCU Academic Integrity Policy
*/
// formatted with https://codebeautify.org/c-formatter-beautifier for improved readability

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <sys/wait.h>

#include <fcntl.h>

#include <sys/stat.h>

#include "myshell.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define DELIMITERS " \t\n"

int main(int argc, char * argv[]) {
    // Print welcome banner
    printShellPrompt();

    char command[MAX_COMMAND_LENGTH];
    char * arguments[MAX_ARGUMENTS];
    int num_arguments;
    FILE * batchFile = NULL;

    // Check if batch file argument is provided
    if (argc > 1) {
        // Open the batch file for reading
        batchFile = fopen(argv[1], "r");
        if (batchFile == NULL) {
            perror("Error opening batch file");
            exit(EXIT_FAILURE);
        }
    }

    // Create the shell loop
    while (1) {
        // Clear arguments array
        memset(arguments, 0, sizeof(char * ) * MAX_ARGUMENTS);

        // Read command input from the batch file or from the user
        if (batchFile != NULL) {
            if (fgets(command, MAX_COMMAND_LENGTH, batchFile) == NULL) {
                // End of file reached
                fclose(batchFile);
                break;
            }
        } else {
            // Print the shell prompt
            printf("%s$ ", getcwd(NULL, 0));

            // Read command input from the user
            fgets(command, MAX_COMMAND_LENGTH, stdin);
        }

        // Tokenize the command into arguments
        num_arguments = 0;
        char * token = strtok(command, DELIMITERS);
        while (token != NULL && num_arguments < MAX_ARGUMENTS - 1) {
            arguments[num_arguments++] = token;
            token = strtok(NULL, DELIMITERS);
        }
        arguments[num_arguments] = NULL; // Null-terminate the argument list

        // Check for redirection symbols
        int input_fd = STDIN_FILENO;
        int output_fd = STDOUT_FILENO;
        for (int i = 0; i < num_arguments; ++i) {
            if (strcmp(arguments[i], "<") == 0) {
                // Input redirection
                arguments[i] = NULL; // Remove "<"
                input_fd = open(arguments[i + 1], O_RDONLY);
                if (input_fd == -1) {
                    perror("Failed to open input file");
                    break;
                }
                i++; // Skip input file argument
            } else if (strcmp(arguments[i], ">") == 0) {
                // Output redirection
                arguments[i] = NULL; // Remove ">"
                output_fd = open(arguments[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                if (output_fd == -1) {
                    perror("Failed to open output file");
                    break;
                }
                i++; // Skip output file argument
            }
        }

        // Handle internal commands
        if (strcmp(arguments[0], "cd") == 0) {
            // Internal cd command
            if (cd(arguments[1]) != 0) {
                // Print error message if cd fails
                fprintf(stderr, "cd: failed to change directory\n");
            }
            continue; // Skip further processing
        } else if (strcmp(arguments[0], "pwd") == 0) {
            // Internal pwd command
            pwd();
            continue;
        } else if (strcmp(arguments[0], "clr") == 0) {
            clr();
            continue;
        } else if (strcmp(arguments[0], "dir") == 0) {
            dir(arguments[1]);
            continue;
        } else if (strcmp(arguments[0], "environ") == 0) {
            printEnviron();
            continue;
        } else if (strcmp(arguments[0], "echo") == 0) {
            // Join the remaining arguments into a single string
            char message[MAX_COMMAND_LENGTH];
            strcpy(message, "");
            for (int i = 1; i < num_arguments; i++) {
                strcat(message, arguments[i]);
                strcat(message, " ");
            }
            // Remove the trailing space
            message[strlen(message) - 1] = '\0';

            // Call the echo function
            echo(message);
            continue;
        } else if (strcmp(arguments[0], "pause") == 0) {
            pauseShell();
            continue;
        } else if (strcmp(arguments[0], "quit") == 0) {
            printf("Shutting Down...\n");
            break;
        }

        // Fork and execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            // Child process
            // Redirect input
            if (input_fd != STDIN_FILENO) {
                if (dup2(input_fd, STDIN_FILENO) == -1) {
                    perror("dup2 input");
                    exit(EXIT_FAILURE);
                }
                close(input_fd);
            }
            // Redirect output
            if (output_fd != STDOUT_FILENO) {
                if (dup2(output_fd, STDOUT_FILENO) == -1) {
                    perror("dup2 output");
                    exit(EXIT_FAILURE);
                }
                close(output_fd);
            }
            // Execute the command
            execvp(arguments[0], arguments);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
            // Close input/output file descriptors
            if (input_fd != STDIN_FILENO)
                close(input_fd);
            if (output_fd != STDOUT_FILENO)
                close(output_fd);
        }
    }

    return 0;
}
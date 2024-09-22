/*
name: Henri Simmons-Hayden
student number: 22422504
I acknowledge the DCU Academic Integrity Policy
*/

#ifndef MYSHELL_H
#define MYSHELL_H

// prototype for initial welcome message
void printShellPrompt();

// prototype for cd command to change directory
int cd(char *directory);

// prototype for pwd command to print working directory
void pwd();

// prototype for clr command to clear the screen
void clr();

// prototype for dir command to list contents and properties of
// everything in the specified directory
void dir(char *directory);

//prototype for environ command to list environment strings
void printEnviron();

// prototype for echo command to output a message to the display
void echo(char *message);

// prototype for pause command to pause operation of shell until
// enter is pressed
void pauseShell();

#endif

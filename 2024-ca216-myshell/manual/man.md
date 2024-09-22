# CA216 - MyShell
This is a rudimentary shell that I have created for the CA216 module, It supports internal and external commands, batch mode and I/O redirection.

# SUPPORTED COMMANDS
A brief guide on how to use the internal commands of the shell

## cd
'cd [directory]'
this command is used to change the current working directory, it can be followed with the name of a directory within the current working directory, or any directory within that by delimiting the directories with '/', for example cd dir1/dir2.
Conversely it can be used to access any directory by supplying the full path to the directory.
You may also follow cd with '..' to move to the parent directory of the current
working directory.
## pwd
'pwd'
this command takes no arguments and simply prints the current working directory
to the screen.
## clr
'clr'
this command clears the screen of all text from within the shell.
## dir
'dir [directory]'
this command can be used on its own and acts upon the current directory or a specified directory. It prints information about the contents of the directory.
## printEnviron
'environ'
this command prints a list of all environment variables.
## echo
'echo [message]'
this command prints a message to the display.
## pauseShell
'pauseShell'
this command pauses all operations until the enter key is pressed.
## quit
'quit'
this command exits the shell

# ENVIRONMENT CONCEPTS
MyShell operates within an environment consisting of multiple settings and variables. These include environment variables which define the shell's behavior. Users can see these variables using the environ command. MyShell inherits the environment of the parent process when executed.

# BATCH MODE
When MyShell is invoked with an additional argument, it will enter batch mode in which the arguments contained in this file will be executed and at the end the shell will exit. While mostly supported the shell will return a segmentation fault at the end of execution, the shell works as normal afterwards.

# I/O REDIRECTION
I/O redirection allows users to direct data between commands and files, these are the supported operators:
## '<'
takes standard input from a file
example 'echo < input.txt'
## '>'
overwrites a file with standard output, creates file if file not present
example 'echo message > output.txt'
## '>>'
works the same as '>' but appends instead of overwrites
example 'echo message >> output.txt'

# REFERENCES
## Bach, M. J. (1986). The Design of the UNIX Operating System. Pearson Education.
## Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). Operating System Concepts. John Wiley & Sons.
## Anderson and P. Anderson (1986), The UNIX C Shell field guide. Englewood Cliffs,  Prentice Hall.
## Kerrisk, M. (2010). The Linux Programming Interface: A Linux and UNIX System Programming Handbook. No Starch Press



# STUDENT INFO
name: Henri Simmons-Hayden
student number: 22422504
I acknowledge the DCU Academic Integrity Policy
# Command-line-shell-in-C
A Unix-style command shell written in C that supports process creation, command execution, background jobs, built-in commands, and interprocess communication through pipes. 
This project is a Linux shell written in C. It is an interactive command line shell which executes external programs using functions such as fork() and execvp(). This project also demonstrates operating system concepts such as waitpid-based synchronization, file descriptor redirection, and dynamic memory allocation.

Features:
Core Shell Functionality:
-	Interactive command-line shell implemented in C 
-	Executes external programs using fork() and execvp() 
-	Custom command prompt 
-	Continuous command-processing loop until exit 

Process Management:
-	Creation of child processes using fork() 
-	Foreground process execution 
-	Parent-child process synchronization using waitpid() 
-	Error handling for process creation failures 

Background Execution:
Supports Unix-style background jobs using &

Pipe Support:
Supports single-stage Unix pipes using |
Implemented using:
-	pipe() 
-	dup2() 
-	Multiple child processes 
-	File descriptor management

Built-in commands: 

cd:
-	Changes shell working directory 
-	Implemented using chdir() 
-	Executed directly in the shell process rather than a child process

exit:
-	Shell termination
-	Memory cleanup before exit

Dynamic Memory Management:
The shell dynamically allocates memory for:
-	Command input buffers 
-	Argument arrays 
-	Pipe command parsing 
Uses:
-	malloc() 
-	realloc() 
-	free()

Command Parsing:
-	Tokenization using strtok() 
-	Parsing of command arguments 
-	Detection of: 
-	pipes (|) 
-	background operators (&) 
-	Construction of argument vectors for execvp()

File Descriptor Manipulation:
Uses:
pipe()
dup2()
close()
to redirect:
-	stdout → pipe write end 
-	stdin → pipe read end

Error Handling:
Handles failures for:
-	invalid commands 
-	failed forks 
-	failed pipes 
-	failed directory changes 
-	failed program execution 
using perror()

Technologies:
-Linux / POSIX APIs
-Process Creation (fork)
-Program Execution (execvp)
-Process Synchronization (waitpid)
-Interprocess Communication (pipe)
-File Descriptor Redirection (dup2)
-Dynamic Memory Management
-Command Parsing
-Unix Shell Design

How to compile and run:
-For MacOS/Linux: 
-Compile: gcc -o shell shell.c
-Run: ./shell
-For Windows: The code will not compile on standard Windows due to the use of Unix/POSIX APIs. A POSIX compatibility layer such as Cygwin will need to be installed. Then use the following commands:
-Compile: gcc -o shell shell.c
-Run: ./shell

Possible improvements:
- Support multiple chained pipes.
- Add input and output redirection.
- Implement background job tracking and cleanup.
- Improve handling of malformed input and edge cases.
- Refactor parsing and execution logic into separate modules.
- Add automated test cases for command parsing and process management.

Author
Developed by Safee ur Rab, a Software Engineering student with an interest in systems programming, operating systems, and low-level software development.
This project was built as part of my effort to strengthen my understanding of Unix/Linux process management, shell design, and C programming.

This Project Was Created To

This project was developed as a systems programming exercise to gain hands-on experience with Unix process management and interprocess communication in C.

The goals of the project were to:

Understand how operating systems create and manage processes using fork().
Execute external programs using the exec family of system calls.
Implement process synchronization using waitpid().
Explore interprocess communication through Unix pipes.
Practice file descriptor manipulation with dup2().
Develop experience with dynamic memory management and command parsing.
Build a simplified command-line shell that demonstrates core operating system concepts.

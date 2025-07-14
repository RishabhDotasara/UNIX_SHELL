# Unix Shell Implementation

A simple Unix shell implementation in C++ that demonstrates fundamental concepts of operating systems including process management, signal handling, and system calls.

## Features

- **Process Management**: Creates child processes using `fork()` to execute commands in isolation
- **Built-in Commands**: Implements essential shell commands like `cd` and `exit`
- **Signal Handling**: Demonstrates signal management for processes using `signal()` system calls
- **Interactive Prompt**: Shows current working directory in the prompt using `getcwd()`
- **Command Parsing**: Parses user input and tokenizes commands with arguments
- **Error Handling**: Proper error reporting using `perror()` for system call failures

## Architecture

- **Parent Process**: Handles user input, command parsing, and built-in commands
- **Child Processes**: Execute external commands using `execvp()` system call
- **Signal Management**: Parent ignores SIGINT while children use default signal behavior
- **Memory Management**: Proper allocation and deallocation of dynamic memory

## Built-in Commands

- `cd <directory>` - Change current working directory
- `exit` - Terminate the shell

## Compilation and Execution

### Prerequisites
- C++ compiler (g++)
- readline library development headers

Install readline library on Ubuntu/Debian:
```bash
sudo apt-get install libreadline-dev
```

### Compile
```bash
g++ -o shell shell.cpp -lreadline
```

### Run
```bash
./shell
```

## Usage Example

```bash
/home/user> ls -la
total 16
drwxr-xr-x 2 user user 4096 Jul 14 10:30 .
drwxr-xr-x 3 user user 4096 Jul 14 10:29 ..
-rwxr-xr-x 1 user user 8760 Jul 14 10:30 shell
-rw-r--r-- 1 user user 3421 Jul 14 10:29 shell.cpp

/home/user> cd /tmp
/tmp> pwd
/tmp

/tmp> exit
```

## Technical Details

### System Calls Used
- `fork()` - Create child processes
- `execvp()` - Execute programs
- `waitpid()` - Wait for child process completion
- `chdir()` - Change directory
- `getcwd()` - Get current working directory
- `signal()` - Handle signals

### Libraries Used
- `unistd.h` - Unix standard definitions
- `sys/wait.h` - Wait for process state changes
- `readline/readline.h` - Interactive line editing
- `signal.h` - Signal handling

## Learning Objectives

This project demonstrates:
- Process creation and management in Unix/Linux
- Inter-process communication concepts
- Signal handling mechanisms
- System call usage and error handling
- Memory management in C++
- Shell command parsing and execution

## Contributions

Contributions are welcome! Feel free to:
- Add new built-in commands
- Improve error handling
- Enhance signal management
- Add command history features
- Implement I/O redirection
- Add pipe support

## License

This project is open source and available under
#include <iostream>
#include <unistd.h>
#include <stdbit.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();
    int stat_loc;

    if (child_pid < 0) {
        // Fork failed
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    } else if (child_pid == 0) {
        // Child process
        std::cout << "Child process: child_pid = " << child_pid << std::endl;
        sleep(1);
        _exit(0); // Exit child process
    } else {
        int status;
        waitpid(child_pid, &stat_loc, WUNTRACED);
        std::cout << "Parent process: Child child_pid = " << child_pid << std::endl;
    }

    return 0;
}
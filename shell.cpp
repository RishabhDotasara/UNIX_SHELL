#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <readline/readline.h>


char **get_input(char *input)
{
    char **command = (char **)malloc(8 * sizeof(char *));
    const char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL)
    {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command ;
}



int main()
{

    char *input;
    char **command;
    pid_t child;
    int stat_loc;
    while (1)
    {
        input = readline("unixsh>");
        command = get_input(input);

        // fork the process 
        child = fork();

        if (child == 0)
        {
            execvp(command[0],command);
        }   
        else 
        {
            waitpid(child, &stat_loc, WUNTRACED);
        }

        free(input);
        free(command);
    }


    return 0;








    // pid_t child_pid = fork();
    

    // if (child_pid < 0)
    // {
    //     std::cout<<"Shell Failed to Start!\n";
    // }
    // else if (child_pid == 0)
    // {
    //     // this is the child process to execute commands in isolation
    //     // protecting the main parent process from crashing if something goes wrong 
    //     // in child process 
    //     std::cout<<"Child Process Spawned with PID: "<<getpid()<<std::endl;
    // }
    // else 
    // {
    //     // this is parent process thread, where we will take the commands from the user
    //     // and then we will spawn a child process to exexute the commands in isolation
    //     // using execvp syscall 
    //     // wait for the child process to finish 
    //     int child_stat;

    //     // here in the parent process, we will run an infinite while loop and keep listening
    //     // for commands from the user and then we will execute them in the child process,
    //     // ig we can access the same data from the parent process, as the child process
    //     // has the same page stats as of the parent process 

    //     waitpid(child_pid, &child_stat, WUNTRACED);
    //     std::cout<<"Child Process with PID "<<child_pid<<" executed!\n";
        
    // }

}
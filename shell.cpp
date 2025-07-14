#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <readline/readline.h>
#include <signal.h>


// SIGNAL HANDLING FOR PROCESSES USIGN signal.h
//  alias for the signal handler function 
typedef void (*sighandler_t) (int); // good topic to study: do look it once

// declaration of the signal handler function 
sighandler_t signal(int sigint, sighandler_t handler);

void signint_handler(int signo)
{
    std::cout<<"SIGNINT Caught!";
}


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

int cd(char *path)
{
    return chdir(path);
}


int main()
{

    signal(SIGINT,SIG_IGN);

    char *input;
    char **command;
    pid_t child;
    int stat_loc;
    while (1)
    {
        char *pwd = getcwd(NULL, 0);
        std::string prompt = std::string(pwd) + ">";
        input = readline(prompt.c_str());

        if (input == NULL)
        {
            std::cout<<"\n";
            exit(0);
        }
        


        free(pwd);
        command = get_input(input);



        // built in commands 
        // These are the commands that have to be executed in the current shell only\
        // like cd, you cannot execute this in the child process and be happy about it.
        // so we will interupt the commands in between, to get the builtin commands
        if (command[0] && strcmp(command[0], "cd") == 0)
        {
            // keep in mind the error handling
            if (cd(command[1]) < 0)
            {
                perror(command[1]);
            }
            continue;
        }
        else if (command[0] && strcmp(command[0], "exit") == 0)
        {
            exit(0);
        }

        // fork the process 
        child = fork();

        if (child == 0)
        {
            // set the default behaivour of sigint in the child process 
            // as the child processes also copy signal behaivours from the parent process 
            signal(SIGINT, SIG_DFL);
            if (execvp(command[0], command) < 0)
            {
                perror(command[0]);
                exit(1);
            }
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
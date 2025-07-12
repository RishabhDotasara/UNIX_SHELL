#include <unistd.h>

int main()
{
    // Example: execute "ls" with argument "-l"
    char *args[] = {"ls", "-l", NULL};
    execvp(args[0], args);
    

}
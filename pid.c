#include <stdio.h>  //
#include <unistd.h>

/**
 * main - prints the PID and PPID
 * current process PID
 * Prarent process PID
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t my_ppid;

    my_pid = getpid();
    my_ppid = getppid();
    printf("PID: %d\n", my_pid);
    printf("PPID: %d\n",my_ppid);
    return (0);
}
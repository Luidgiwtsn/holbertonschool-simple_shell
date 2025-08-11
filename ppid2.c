#include <stdio.h>
#include <unistd.h>

/**
 * main - Prints the PID and PPID of the current process
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid, my_ppid;
	

	my_pid = getpid();    /* Récupère le PID du processus courant */
	my_ppid = getppid();  /* Récupère le PID du processus parent */

	printf("PID : %d\n", my_pid);
	printf("PPID: %d\n", my_ppid);

	return (0);
}

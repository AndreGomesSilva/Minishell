#include "../../include/minishell.h"

void receive_sig_int(int sig) {
    printf("Recebeu o sinal SIGINT (Ctrl + C)\n");
}

void receive_sigquit(int sig) {
    printf("Recebeu o sinal SIGQUIT (Ctrl + \\)\n");
}

void handle_signal(void)
{
	signal(SIGINT, receive_sig_int);
	signal(SIGQUIT, receive_sigquit);

	printf("\nCtrl+D (EOF) signal received. Exiting the shell.\n");
	clear_history(); // Clear the history before exiting
	exit(0); // Exit the program
}


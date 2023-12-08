#include "../../include/minishell.h"

void receive_sig_int(int sig) {
    printf("Sinal: %d, Recebeu o sinal SIGINT (Ctrl + C)\n", sig);
}

void receive_sigquit(int sig) {
    printf("Sinal: %d, Recebeu o sinal SIGQUIT (Ctrl + \\)\n", sig);
}

void handle_signal(void)
{
	extern t_control *control;
	signal(SIGINT, receive_sig_int);
	signal(SIGQUIT, receive_sigquit);

	printf("\nCtrl+D (EOF) signal received. Exiting the shell.\n");
	clear_history();
	exit(0);
}


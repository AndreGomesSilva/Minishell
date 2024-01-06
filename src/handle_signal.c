#include "../include/minishell.h"
#include <readline/readline.h>

void receive_sig_int(int sig) {
	extern t_control *g_control;
	free_cmd(g_control);
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
   	rl_redisplay();
}

void receive_sigquit(int sig) {
    printf("exit\n");
}

void handle_signal(void)
{
	extern t_control *g_control;
	signal(SIGINT, receive_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

// FIXME: Ctrl + C = apaga o que esta no buffer e desenha uma nova linha
#include "../include/minishell.h"
#include <readline/readline.h>

int	receive_signal_ctrl_d(t_control *control)
{
	clear_history();
	general_free(control);
	exit(0);
}

void receive_sig_int(int sig) {
	(void) sig;
	extern t_control *g_control;
	free_cmd(g_control);
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
   	rl_redisplay();
}

void receive_sigquit(int sig) {
	(void) sig;
//	sig  = 0;
    printf("exit\n");
}

void handle_signal(void)
{
	extern t_control *g_control;
	signal(SIGINT, receive_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

// FIXME: Ctrl + C = apaga o que esta no buffer e desenha uma nova linha
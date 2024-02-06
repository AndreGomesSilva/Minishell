#include "../include/minishell.h"

t_control	*g_control;

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	g_control = NULL;
	if (argc > 1)
		return (0);
	handle_config(&g_control, env);
	handle_signal();
	print_sort_env(g_control);
//	while (1)
//		middleware(g_control);
//	clear_history();
	return (0);
}

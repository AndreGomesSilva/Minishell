#include "../include/minishell.h"

t_control	*g_control;

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	for(int i=0;env[i];i++)
	{
		printf("%s\n",env[i]);
	}
	// (void)argv;
	// g_control = NULL;
	// if (argc > 1)
	// 	return (0);
	// handle_config(&g_control, env);
	// handle_signal();
	// handle_envp(g_control, env);
	// while (1)
	// 	middleware(g_control);
	// print_lst(g_control->cmd);
	// clear_history();
	// free_cmd(g_control);

	return (0);
}

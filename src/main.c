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
	 handle_envp(g_control, env);
	printf("\n %s \n", get_var_value(g_control, "LOGNAME"));
	free_hash_table(g_control->env_table);
//	 while (1)
//	 	middleware(g_control);
//	 print_lst(g_control->cmd);
//	 clear_history();
//	 free_cmd(g_control);

	return (0);
}

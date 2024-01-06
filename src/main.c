#include "../include/minishell.h"

static void	print_lst(t_cmd *cmd)
{
	printf("number of nodes: %d\n", list_len(cmd));
	while (cmd)
	{
		printf("%s\n", cmd->cmd);
		cmd = cmd->next;
	}
}

t_control	*g_control;

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	g_control = NULL;
	handle_start(&g_control, env);
	handle_signal();
	if (argc > 1)
		return (0);

	while (1)
	{
		handle_token(g_control);
		handle_expander(g_control, env);
		print_lst(g_control->cmd);
	}
	print_lst(g_control->cmd);
	clear_history();
	free_cmd(g_control);
	return (0);
}

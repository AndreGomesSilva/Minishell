#include "../include/minishell.h"

static void    print_lst(t_cmd *cmd)
{
    printf("number of nodes: %d\n", list_len(cmd));
	printf("types 3 == AND,  2 == OR, 1 == PIP\n");
	printf("\n---------------------------------\n");
    while (cmd)
    {
        printf("CMD: %s --- type: %d \n", cmd->cmd, cmd->type);
        while (cmd->list_args)
        {
            printf("ARG: %s --- type: %d \n", cmd->list_args->arg, cmd->list_args->type);
            cmd->list_args = cmd->list_args->next;
        }
        printf("\n---------------------------------\n");
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
		// handle_expander(g_control, env);
		print_lst(g_control->cmd);
	}
	print_lst(g_control->cmd);
	clear_history();
	free_cmd(g_control);
	return (0);
}

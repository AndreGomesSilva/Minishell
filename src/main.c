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

int	handle_input(t_control *control)
{
	char	*input;
	char	*first_input;

	input = readline(control->prompt);
	first_input = input;
	if (input)
	{
		add_history(input);
		while (*input)
		{
			while (is_space(*input))
				input++;
			if (*input)
				input = handle_token(control, input);
		}
		handle_expander(control, control->env);
		print_lst(g_control->cmd);
		free(first_input);
		free_cmd(control);
		return (TRUE);
	}
	else
		receive_signal_ctrl_d(control);
	return (FALSE);
}

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
		handle_input(g_control);
	}
	print_lst(g_control->cmd);
	clear_history();
	free_cmd(g_control);
	return (0);
}

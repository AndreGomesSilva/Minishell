#include "../include/minishell.h"

static void	print_lst(t_lst *current)
{
	printf("number of nodes: %d\n", list_len(current));
	while (current)
	{
		printf("%s\n", current->token_name);
		current = current->next;
	}
}

t_control	*g_control;

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	g_control = NULL;
	handle_start(&g_control);
	handle_signal();
	if (argc > 1) {
		return (0);
	}

	while (1)
	{
		take_input(g_control);
		handle_expander(g_control, env);
		print_lst(g_control->lst);
	}
	print_lst(g_control->lst);
	clear_history();
	free_lst(g_control);
	return (0);
}

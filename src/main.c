#include "../include/minishell.h"

static void	print_lst(t_lst **lst)
{
	t_lst	*current;

	current = *lst;
	printf("number of nodes: %d\n", list_len(lst));
	while (current)
	{
		printf("%s\n", current->token_name);
		current = current->next;
	}
}

int	main(int argc, char **argv)
{
	t_lst	*lst;
	(void) argv;
	lst = NULL;
	if(argc > 1)
		return (0);
//	signal(SIGUSR1, handle_sign);
	while (1)
		take_input(&lst);
	print_lst(&lst);
	clear_history();
	free_lst(&lst);
	return (0);
}

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

static void	handle_sign(int sig)
{
	// g_runtime = 0;
}
int	main(void)
{
	if(!handle_entry_validation(argc))
		return (0);
	t_lst	*lst;
	char	**cmd;

	lst = NULL;
	create_main_node(&lst, "ls");
	create_main_node(&lst, "grep");
	signal(SIGUSR1, handle_sign);

	cmd = ft_split(readline("> "), ' ');
	token_factory(&lst, cmd);
	print_lst(&lst);
	free_matrix(cmd);
	while(1)
		;
	return (0);
}

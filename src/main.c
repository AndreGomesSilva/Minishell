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

//static void	handle_sign(int sig)
//{
//	// g_runtime = 0;
//}

int	take_input(t_lst **lst)
{
	char	**input_matrix;
	char	*input;

	input = readline("> ");
	if (input)
	{
		input_matrix = ft_split(input, ' ');
		token_factory(lst, input_matrix);
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

int	main(void)
{
//	if(!handle_entry_validation(argc))
//		return (0);
	t_lst	*lst;

	lst = NULL;
//	signal(SIGUSR1, handle_sign);
	take_input(&lst);
	print_lst(&lst);

	free_lst(&lst);
//	while(1)
//		;
	return (0);
}

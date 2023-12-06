/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:48:23 by angomes-          #+#    #+#             */
/*   Updated: 2023/12/06 15:06:11 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	lst = NULL;
	create_main_node(&lst, "ls");
	create_main_node(&lst, "grep");
	signal(SIGUSR1, handle_sign);


	while(1)
		;	
	return(0);
}

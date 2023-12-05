/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:48:23 by angomes-          #+#    #+#             */
/*   Updated: 2023/12/04 19:47:49 by r-afonso         ###   ########.fr       */
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

int	main(void)
{
	t_lst	*lst;
	lst = NULL;
	create_main_node(&lst, "ls");
	create_main_node(&lst, "grep");
	print_lst(&lst);
	printf("Ola Mundo");
	return (0);
}

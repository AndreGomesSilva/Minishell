//
// Created by Alaide e Julio on 28/12/2023.
//

#include "../../include/minishell.h"

void	set_type(t_lst *lst)
{
	t_lst	*node;
	int		type;

	if (!lst)
		return ;

	node = lst;
	while (node)
	{
		type = 0;
		type = is_delimiter(node->token_name[0]);
		if (type)
		{
			if (type == 3)
				node->type = PIP;
			else if (type == 2)
			{
				if (is_delimiter(node->token_name[1]))
					node->type = HER;
				else
					node->type = RED;
			}
		}
		node = node->next;
	}
}
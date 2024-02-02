//
// Created by angomes- on 2/2/24.
//

#include "../include/minishell.h"

void	print_errors(char *type, int flag)
{
	if (!ft_strncmp(type, "syntax", 5))
	{
		if (flag == 1)
			ft_putstr_fd("syntax error near unexpected token `|' \n", 2);
	}
}
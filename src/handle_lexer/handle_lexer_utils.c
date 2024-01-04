//
// Created by Alaide e Julio on 28/12/2023.
//

#include "../../include/minishell.h"

int 	is_space(char c)
{
	if (c != 0 && c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

int is_delimiter(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else if (c == '>' || c == '<')
		return (2);
	else if (c == '|')
		return (3);
	else
		return (0);
}

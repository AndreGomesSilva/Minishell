/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:15:24 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/13 00:52:55 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_absolute_path(char *cmd)
{
	while (cmd && *cmd && cmd++)
		if (*cmd == '/')
			return (TRUE);
	return (FALSE);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!str_compare(cmd, "echo"))
		return (B_ECHO);
	else if (!str_compare(cmd, "cd"))
		return (B_CD);
	else if (!str_compare(cmd, "pwd"))
		return (B_PWD);
	else if (!str_compare(cmd, "env"))
		return (B_ENV);
	else if (!str_compare(cmd, "export"))
		return (B_EXPORT);
	else if (!str_compare(cmd, "unset"))
		return (B_UNSET);
	else if (!str_compare(cmd, "exit"))
		return (B_EXIT);
	return (B_NOBT);
}

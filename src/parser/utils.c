/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:15:24 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/11 15:55:48 by angomes-         ###   ########.fr       */
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
		return (ECHO);
	else if (!str_compare(cmd, "cd"))
		return (CD);
	else if (!str_compare(cmd, "pwd"))
		return (PWD);
	else if (!str_compare(cmd, "env"))
		return (ENV);
	else if (!str_compare(cmd, "export"))
		return (EXPORT);
	else if (!str_compare(cmd, "unset"))
		return (UNSET);
	else if (!str_compare(cmd, "exit"))
		return (EXIT);
	return (NOBT);
}

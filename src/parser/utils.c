/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:15:24 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/08 16:32:26 by r-afonso         ###   ########.fr       */
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
	int	len;

	if (!cmd)
		return (FALSE);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", len))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", len))
		return (PWD);
	else if (!ft_strncmp(cmd, "env", len))
		return (ENV);
	else if (!ft_strncmp(cmd, "export", len))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", len))
		return (UNSET);
	else if (!ft_strncmp(cmd, "exit", len))
		return (EXIT);
	return (NOBT);
}

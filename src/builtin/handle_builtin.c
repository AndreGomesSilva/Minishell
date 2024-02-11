/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:49:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/11 23:10:04 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtin(char **cmd, int fd)
{
	const enum e_type_error	builtin = is_builtin(cmd[0]);

	if (builtin == CD || builtin == ECHO || builtin == EXPORT
		|| builtin == UNSET || builtin == ENV || builtin == EXIT
		|| builtin == PWD)
	{
		if (builtin == CD)
			if (handle_builtin_cd(cmd[1]) == TRUE)
				return (TRUE);
		if (builtin == ECHO)
		{
			handle_echo(cmd, fd);
			return (TRUE);
		}
		// else if (handle_builtin_cd(cmd[0], "echo", 5) == 0)
		//		handle_echo(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		//		handle_exit(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		//		handle_env(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		//		handle_export(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		//		handle_unset(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		//		handle_cd(cmd, fd);
		//	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		//		handle_pwd(cmd, fd);
	}
	else
		return (FALSE);
}

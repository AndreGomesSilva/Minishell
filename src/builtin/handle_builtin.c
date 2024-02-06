/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:49:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/05 23:59:15 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		make_echo(cmd);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		make_exit(cmd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		make_env(cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		make_export(cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		make_unset(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		make_cd(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		make_pwd(cmd);
}
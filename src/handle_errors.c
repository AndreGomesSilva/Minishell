/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/17 19:16:06 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_simple_error(char *error)
{
	if (!ft_strncmp(error, "EXPORT", 6))
		ft_putstr_fd("export: Invalid command \n", 2);
	else if (!ft_strncmp(error, "UNSET", 5))
		ft_putstr_fd("unset: Invalid command \n", 2);
	else if (!ft_strncmp(error, "PWD", 4))
		ft_putstr_fd("pwd: too many arguments \n", 2);
	else if (!ft_strncmp(error, "CD_NO_ARG", 10))
		ft_putstr_fd("cd: too many arguments \n", 2);
	else if (!ft_strncmp(error, "CD_NO_EXIST", 12))
		ft_putstr_fd("cd: no such file or directory \n", 2);
}

void	print_error(t_cmd *ptr_cmd, enum e_type_error error)
{
	ptr_cmd->error_type = error;
	if (ptr_cmd->error_type == E_SYNTAX)
		ft_putstr_fd("Error: Syntax \n", 2);
	else if (ptr_cmd->error_type == E_CMD_NO_FOUND)
	{
		ft_putstr_fd(ptr_cmd->cmd, 2);
		ft_putstr_fd(": Command not found \n", 2);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/21 20:02:12 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

void	print_simple_error(char *error)
{
	if (!ft_strncmp(error, "EXPORT", 6))
		perror("export");
	else if (!ft_strncmp(error, "UNSET", 5))
		perror("unset");
	else if (!ft_strncmp(error, "PWD", 4))
		perror("pwd");
	else if (!ft_strncmp(error, "CD_NO_EXIST", 12))
		perror("cd");
	else if (!ft_strncmp(error, "ENV", 4))
		printf("%s","env: Syntax error\n");
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
		exit(127);
	}
	else if (ptr_cmd->error_type == E_NO_FILE)
	{
		ft_putstr_fd("Error: No such file or directory \n", 2);
		exit(127);
	}
	else if (ptr_cmd->error_type == E_PERMISSION)
	{
		ft_putstr_fd("Error: Permission denied \n", 2);
		exit(126);
	}
	else if (ptr_cmd->error_type == E_NO_ERROR)
		exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/28 16:20:59 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_error(t_cmd *ptr_cmd, enum e_type_error error)
{
	ptr_cmd->error_type = error;
	if (ptr_cmd->error_type == E_SYNTAX)
	{
		ft_putstr_fd("Error: Syntax \n", 2);
		return (EXIT_FAILURE);
	}
	else if (ptr_cmd->error_type == E_CMD_NO_FOUND)
	{
		ft_putstr_fd(ptr_cmd->cmd, 2);
		ft_putstr_fd("Error: Command not found \n", 2);
		return (127);
	}
	else if (ptr_cmd->error_type == E_NO_FILE)
	{
		ft_putstr_fd("Error: No such file or directory \n", 2);
		return (EXIT_FAILURE);
	}
	else if (ptr_cmd->error_type == E_PERMISSION)
	{
		ft_putstr_fd("Error: Permission denied \n", 2);
		return (1);
	}
	else if (ptr_cmd->error_type == E_IS_DIR)
	{
		ft_putstr_fd("Error: Is a directory \n", 2);
		return (126);
	}
	else if (ptr_cmd->error_type == E_NO_ERROR)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/29 18:35:40 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_error(t_cmd *ptr_cmd)
{
	char	*error_msg;
	int		error_code;
	
	error_msg = NULL;
	error_code = EXIT_FAILURE;
	if (ptr_cmd->error_type == E_SYNTAX)
	{
		error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]),
				ft_strdup(": Syntax \n"));
		ft_putstr_fd(error_msg, 2);
		error_code = EXIT_FAILURE;
	}
	else if (ptr_cmd->error_type == E_CMD_NO_FOUND)
	{
		error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]), ft_strdup(": Command not found \n"));
		ft_putstr_fd(error_msg, 2);
		error_code = 127;
	}
	else if (ptr_cmd->error_type == E_NO_FILE)
	{
		error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]), ft_strdup(": No such file or directory \n"));
		ft_putstr_fd(error_msg, 2);
		error_code = EXIT_FAILURE;
	}
	else if (ptr_cmd->error_type == E_NO_FILE_2)
	{
		error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]), ft_strdup(": No such file or directory \n"));
		ft_putstr_fd(error_msg, 2);
		error_code = 127;
	}
	else if (ptr_cmd->error_type == E_PERMISSION)
	{
		error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]), ft_strdup(": Permission denied \n"));
		ft_putstr_fd(error_msg, 2);
		error_code = 1;
	}
	else if (ptr_cmd->error_type == E_PERMISSION_2)
	{
		error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]), ft_strdup(": Permission denied \n"));
		ft_putstr_fd(error_msg, 2);
		error_code = 126;
	}
	else if (ptr_cmd->error_type == E_IS_DIR)
	{
		error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]), ft_strdup(": Is a directory \n"));
		ft_putstr_fd(error_msg, 2);
		error_code = 126;
	}
	else if (ptr_cmd->error_type == E_NO_ERROR)
		error_code = EXIT_SUCCESS;
	if (error_msg)
		free(error_msg);
	return (error_code);
}

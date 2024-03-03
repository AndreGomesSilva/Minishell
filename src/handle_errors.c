/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/03 19:55:47 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_error_126(t_cmd *ptr_cmd, int error_code, char **error_msg)
{
	if (ptr_cmd->error_type == E_PERMISSION_2)
	{
		*error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]),
				ft_strdup(": Permission denied \n"));
		ft_putstr_fd(*error_msg, 2);
		error_code = 126;
	}
	else if (ptr_cmd->error_type == E_IS_DIR)
	{
		*error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]),
				ft_strdup(": Is a directory \n"));
		ft_putstr_fd(*error_msg, 2);
		error_code = 126;
	}
	return (error_code);
}

int	print_error_127(t_cmd *ptr_cmd, int error_code, char **error_msg)
{
	if (ptr_cmd->error_type == E_CMD_NO_FOUND)
	{
		*error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]),
				ft_strdup(": Command not found \n"));
		ft_putstr_fd(*error_msg, 2);
		error_code = 127;
	}
	else if (ptr_cmd->error_type == E_NO_FILE_2)
	{
		*error_msg = swap_string(ft_strdup(ptr_cmd->cmd_and_args[0]),
				ft_strdup(": No such file or directory \n"));
		ft_putstr_fd(*error_msg, 2);
		error_code = 127;
	}
	return (error_code);
}

int	print_error_2(t_cmd *ptr_cmd, int error_code)
{
	if (ptr_cmd->error_type == E_PIPE)
	{
		ft_putstr_fd("Error: syntax error near unexpected token `|' \n", 2);
		error_code = 2;
	}
	else if (ptr_cmd->error_type == E_REDIRECT)
	{
		ft_putstr_fd("Error: syntax error near unexpected token \n", 2);
		error_code = 2;
	}
	else if (ptr_cmd->error_type == E_QUOTE)
	{
		ft_putstr_fd(
			"Error: syntax error near unexpected token `\"' or '`' \n", 2);
		error_code = 2;
	}
	return (error_code);
}

int	print_error_1(t_cmd *ptr_cmd, int error_code)
{
	if (ptr_cmd->error_type == E_NO_FILE)
	{
		ft_putstr_fd("Error: No such file or directory \n", 2);
		error_code = 1;
	}
	else if (ptr_cmd->error_type == E_PERMISSION)
	{
		ft_putstr_fd("Error: Permission denied \n", 2);
		error_code = 1;
	}
	else if (ptr_cmd->error_type == E_AMBIGUOUS)
	{
		ft_putstr_fd("Error: Ambiguous redirect \n", 2);
		error_code = 1;
	}
	return (error_code);
}

int	print_error(t_cmd *ptr_cmd)
{
	char	*error_msg;
	int		error_code;

	error_msg = NULL;
	error_code = 0;
	error_code = print_error_126(ptr_cmd, error_code, &error_msg);
	error_code = print_error_127(ptr_cmd, error_code, &error_msg);
	error_code = print_error_2(ptr_cmd, error_code);
	error_code = print_error_1(ptr_cmd, error_code);
	if (ptr_cmd->error_type == E_NO_ERROR)
		error_code = EXIT_SUCCESS;
	if (error_msg)
		free(error_msg);
	return (error_code);
}

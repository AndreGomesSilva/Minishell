/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:33:41 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/07 14:55:54 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_full_cmd(t_cmd *cmd)
{
	int		len;
	char	**args;
	int		i;
	t_arg	*ptr_arg;

	args = NULL;
	type_io_file(cmd);
	len = count_args(cmd);
	if (cmd && len > 0)
	{
		i = 0;
		ptr_arg = cmd->list_args;
		args = (char **)ft_calloc(len + 1, sizeof(char *));
		if (cmd->cmd && cmd->type < REDIRECT_HERD && !(cmd->type == VAR_EXPAND
				&& cmd->cmd[0] == '\0' && len > 1))
			args[i++] = ft_strdup(cmd->cmd);
		while (ptr_arg)
		{
			if (ptr_arg->arg && ptr_arg->type < REDIRECT_HERD
				&& !(ptr_arg->type == VAR_EXPAND && ptr_arg->arg[0] == '\0'))
				args[i++] = ft_strdup(ptr_arg->arg);
			ptr_arg = ptr_arg->next;
		}
	}
	return (args);
}

char	*new_cmd_absolute_path(char **matrix)
{
	char	*result;
	int		len;
	char	*cmd;

	cmd = matrix[0];
	len = 0;
	result = NULL;
	len = (int)ft_strlen(cmd);
	if (len > 0)
	{
		while (--len, cmd[len])
		{
			if (cmd[len] == '/')
			{
				result = ft_substr(&cmd[len], len, ft_strlen(&cmd[len]));
				free(matrix[0]);
				return (result);
			}
		}
	}
	return (result);
}

int	handle_cmd_n_found(char *cmd)
{
	DIR	*directory;

	if ((cmd[0] == '.' && !cmd[1]))
		return (E_IS_DOT);
	else if (is_a_directory(cmd) || !ft_strncmp(cmd, "/", 2))
	{
		directory = opendir(cmd);
		if (directory)
		{
			closedir(directory);
			return (E_IS_DIR_2);
		}
		else if (!access(cmd, F_OK) && access(cmd, X_OK))
			return (E_PERMISSION_2);
		else if (access(cmd, F_OK))
			return (E_NO_FILE_2);
	}
	return (E_NO_ERROR);
}

void	is_command_true(t_cmd *ptr_cmd, t_control *control)
{
	while (ptr_cmd)
	{
		ptr_cmd->cmd_and_args = create_full_cmd(ptr_cmd);
		if (ptr_cmd->cmd_and_args)
		{
			ptr_cmd->path_cmd = handle_bin_path(control,
					ptr_cmd->cmd_and_args[0]);
			if (!is_builtin(ptr_cmd->cmd_and_args[0]) && !is_valid_cmd(ptr_cmd))
				ptr_cmd->error_type = E_CMD_NO_FOUND;
			if (handle_cmd_n_found(ptr_cmd->cmd_and_args[0]))
				control->cmd->error_type
					= handle_cmd_n_found(ptr_cmd->cmd_and_args[0]);
			else
			{
				if (is_a_directory(ptr_cmd->cmd_and_args[0]))
					ptr_cmd->cmd_and_args[0]
						= new_cmd_absolute_path(ptr_cmd->cmd_and_args);
			}
		}
		ptr_cmd = ptr_cmd->next;
	}
}

void	handle_parser(t_control *control)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = control->cmd;
	if (handle_syntax_error(ptr_cmd))
	{
		control->fatal_err = 1;
		return ;
	}
	remove_dolar_follow_quotes(ptr_cmd);
	handle_quotes_parsing(control);
	is_command_true(ptr_cmd, control);
}

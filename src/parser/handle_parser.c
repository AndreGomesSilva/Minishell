/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:33:41 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/28 17:27:27 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_full_cmd(t_cmd *cmd)
{
	int		len;
	char	**args;
	int		i;
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	args = NULL;
	type_io_file(ptr_cmd);
	len = count_args(ptr_cmd);
	if (ptr_cmd && len > 0)
	{
		i = 0;
		ptr_arg = ptr_cmd->list_args;
		args = (char **)ft_calloc(len + 1, sizeof(char *));
		if (ptr_cmd->cmd && ptr_cmd->type < REDIRECT_HERD)
			args[i++] = ft_strdup(ptr_cmd->cmd);
		while (ptr_arg)
		{
			if (ptr_arg->arg && ptr_arg->type < REDIRECT_HERD)
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

int	handle_command_not_found(t_cmd *cmd)
{
	DIR	*directory;

	if (is_absolute_path(cmd->cmd))
	{
		directory = opendir(cmd->cmd);
		if (directory)
		{
			closedir(directory);
			return (E_IS_DIR);
		}
		else if (!access(cmd->cmd, F_OK) && access(cmd->cmd, X_OK))
			return (E_PERMISSION);
		else if (access(cmd->cmd, F_OK))
			return (E_NO_FILE);
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
			else
			{
				if (is_absolute_path(ptr_cmd->cmd_and_args[0]))
					ptr_cmd->cmd_and_args[0] = new_cmd_absolute_path(
							ptr_cmd->cmd_and_args);
			}
			control->cmd->error_type = handle_command_not_found(ptr_cmd);
		}
		ptr_cmd = ptr_cmd->next;
	}
}

void	handle_parser(t_control *control, t_cmd *ptr_cmd)
{
	ptr_cmd = control->cmd;
	if (handle_syntax_error(ptr_cmd))
	{
		control->fatal_err = 1;
		return ;
	}
	handle_quotes_parsing(control);
	is_command_true(ptr_cmd, control);
}

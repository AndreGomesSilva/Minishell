/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:33:41 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/27 13:32:03 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	type_io_file(t_cmd *cmd)
{
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	while (ptr_cmd)
	{
		ptr_arg = ptr_cmd->list_args;
		if (ptr_cmd->type > REDIRECT_HERD && ptr_arg && (ptr_arg->type == NORM
				|| ptr_arg->type == VAR_EXPAND))
		{
			ptr_arg->type = IOFILE;
			ptr_arg = ptr_arg->next;
		}
		while (ptr_arg)
		{
			if ((ptr_arg->type > REDIRECT_HERD && ptr_arg->type < IOFILE)
				&& ptr_arg->next && (ptr_arg->next->type == NORM
					|| ptr_arg->next->type == VAR_EXPAND))
				ptr_arg->next->type = IOFILE;
			ptr_arg = ptr_arg->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
}

int	count_args(t_cmd *cmd)
{
	int		count;
	t_cmd	*ptr_cmd;
	t_arg	*ptr_arg;

	ptr_cmd = cmd;
	ptr_arg = ptr_cmd->list_args;
	count = 0;
	if (ptr_cmd && ptr_cmd->type < REDIRECT_HERD)
		count++;
	while (ptr_arg)
	{
		if (ptr_arg->type < REDIRECT_HERD)
			count++;
		ptr_arg = ptr_arg->next;
	}
	if (count < 0)
		return (0);
	return (count);
}

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

void	handle_parser(t_control *control)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = control->cmd;
	if (handle_syntax_error(ptr_cmd))
	{
		control->fatal_err = 1;
		return ;
	}
	handle_quotes_parsing(control);
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
					ptr_cmd->cmd_and_args[0] = new_cmd_absolute_path(ptr_cmd->cmd_and_args);
			}
		}
		ptr_cmd = ptr_cmd->next;
	}
}

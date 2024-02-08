/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:33:41 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/08 16:31:35 by r-afonso         ###   ########.fr       */
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
		if (ptr_cmd->type >= REDIRECT_HERD && ptr_arg && (ptr_arg->type == NORM
				|| ptr_arg->type == VAR_EXPAND))
		{
			ptr_arg->type = IOFILE;
			ptr_arg = ptr_arg->next;
		}
		while (ptr_arg)
		{
			if (ptr_arg->type >= REDIRECT_HERD && ptr_arg->next
				&& (ptr_arg->next->type == NORM
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
	if (ptr_cmd->type < REDIRECT_HERD)
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
	if (ptr_cmd)
	{
		i = 0;
		len = count_args(ptr_cmd);
		ptr_arg = ptr_cmd->list_args;
		args = (char **)ft_calloc(len + 1, sizeof(char *));
		if (ptr_cmd->type < REDIRECT_HERD)
			args[i++] = ft_strdup(ptr_cmd->cmd);
		while (ptr_arg)
		{
			if (ptr_arg->type < REDIRECT_HERD)
				args[i++] = ft_strdup(ptr_arg->arg);
			ptr_arg = ptr_arg->next;
		}
	}
	return (args);
}

char	*new_cmd_absolute_path(t_cmd *cmd)
{
	char	*ptr_cmd;
	char	*result;
	int		len;

	len = 0;
	ptr_cmd = cmd->cmd;
	result = NULL;
	len = (int)ft_strlen(ptr_cmd);
	if (len > 0)
		while (--len, ptr_cmd[len])
		{
			if (ptr_cmd[len] == '/')
			{
				result = ft_substr(&ptr_cmd[len], len,
						ft_strlen(&ptr_cmd[len]));
				free(cmd->cmd);
				return (result);
			}
		}
	return (result);
}

int	handle_parser(t_control *control)
{
	t_cmd	*ptr_cmd;
	int		result;

	ptr_cmd = control->cmd;
	result = 0;
	if (handle_syntax_error(ptr_cmd))
	{
		print_errors("syntax", 1);
		result = TRUE;
	}
	else
		while (ptr_cmd)
		{
			ptr_cmd->path_cmd = handle_bin_path(control, ptr_cmd);
			if (is_absolute_path(ptr_cmd->cmd))
				ptr_cmd->cmd = new_cmd_absolute_path(ptr_cmd);
			ptr_cmd->cmd_and_args = create_full_cmd(ptr_cmd);
			ptr_cmd = ptr_cmd->next;
		}
	return (result);
}

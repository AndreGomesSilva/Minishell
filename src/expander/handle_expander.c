/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:22 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/11 16:19:40 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_in_quotes(t_control *control, int *i, char *str)
{
	char	type_quote;

	type_quote = str[*i];
	if (type_quote == '\'')
	{
		if (str[*i])
			*i = *i + 1;
		while (str[*i] && str[*i] != type_quote)
			*i = *i + 1;
		if (str[*i])
			*i = *i + 1;
	}
	if (type_quote == '"')
	{
		if (str[*i])
			*i = *i + 1;
		while (str[*i] && str[*i] != type_quote)
			str = expand_var(control, i, str);
		if (str[*i] == '"')
			*i = *i + 1;
	}
	return (str);
}

char	*get_var_in_node(t_control *control, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
			str = get_var_in_quotes(control, &i, str);
		else
			str = expand_var(control, &i, str);
	}
	return (str);
}

static void	get_var_in_arg(t_control *control, t_cmd *cmd)
{
	t_arg	*temp_arg_node;
	t_arg	*arg_node;

	arg_node = cmd->list_args;
	while (arg_node)
	{
		temp_arg_node = arg_node->next;
		if (arg_node->type == VAR_EXPAND || look_exit_variabel(NULL, arg_node))
		{
			arg_node->prev_type = VAR_EXPAND;
			arg_node->arg = get_var_in_node(control, arg_node->arg);
		}
		arg_node = temp_arg_node;
	}
}

int	handle_expander(t_control *control)
{
	t_cmd	*cmd_node_temp;
	t_cmd	*cmd_node;

	cmd_node = control->cmd;
	while (cmd_node && cmd_node->cmd)
	{
		cmd_node_temp = cmd_node->next;
		if (cmd_node->type == VAR_EXPAND || look_exit_variabel(cmd_node, NULL))
			cmd_node->cmd = get_var_in_node(control, cmd_node->cmd);
		get_var_in_arg(control, cmd_node);
		cmd_node = cmd_node_temp;
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:22 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/11 20:24:08 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_join_var(t_control *control, char *str, char *var, char *end)
{
	char	*result;
	char	*temp;
	char	*expand_var;

	result = NULL;
	expand_var = get_var(control, var);
	if (expand_var)
	{
		expand_var = ft_strdup(expand_var);
		temp = ft_strjoin(str, expand_var);
		result = ft_strjoin(temp, end);
		free(str);
		free(expand_var);
		free(var);
		free(temp);
	}
	else
	{
		result = ft_strjoin(str, end);
		free(str);
		free(var);
	}
	return (result);
}

char	*get_var_in_node(t_control *control, char *str)
{
	char	*var;
	char	*ptr_str;
	int		i;
	int		j;

	i = 0;
	ptr_str = str;
	while (str[i])
	{
		if (is_variable(&str[i]))
		{
			j = 0;
			while (ft_isalnum(str[i + 1 + j]) || str[i + 1 + j] == '_')
				j++;
			var = ft_substr(&str[i + 1], 0, j);
			str = ft_join_var(control, ft_substr(str, 0, i), var, &str[i + 1
					+ j]);
			i = 0;
		}
		i++;
	}
	if (ptr_str && *str == '\0')
		free(ptr_str);
	return (str);
}

static int	get_var_in_arg(t_control *control, t_cmd *node)
{
	t_arg	*temp_arg_node;
	t_arg	*arg_node;

	arg_node = node->list_args;
	while (arg_node)
	{
		temp_arg_node = arg_node->next;
		if (arg_node->type == BROKEN_QUOTES)
			return (FALSE);
		if (arg_node->type == VAR_EXPAND)
			arg_node->arg = get_var_in_node(control, arg_node->arg);
		arg_node = temp_arg_node;
	}
	return (TRUE);
}

int	handle_expander(t_control *control)
{
	t_cmd	*cmd_node_temp;
	t_cmd	*cmd_node;

	cmd_node = control->cmd;
	while (cmd_node)
	{
		cmd_node_temp = cmd_node->next;
		if (cmd_node->type == VAR_EXPAND)
			cmd_node->cmd = get_var_in_node(control, cmd_node->cmd);
		if (!get_var_in_arg(control, cmd_node)
			|| cmd_node->type == BROKEN_QUOTES)
		{
			print_error(cmd_node, SYNTAX);
			return (FALSE);
		}
		cmd_node = cmd_node_temp;
	}
	return (TRUE);
}

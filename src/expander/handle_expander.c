/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:22 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/23 10:26:13by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_join_var(t_control *control, char *str, char *var, char *end)
{
	char	*result;
	char	*temp;
	char	*expand_var;

	result = NULL;
	expand_var = get_var_env(control, var);
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

char    *expand_var(t_control *control, int *i, char *str)
{
	char	*new_str;
	char	*var;
	int		j;
	
	if (str[*i] && (is_variable(&str[*i]) || is_exit_variable(&str[*i])))
		{
			j = 0;
			while (ft_isalnum(str[*i + 1 + j]) || str[*i + 1 + j] == '_' || str[*i + 1 + j] == '?')
				j++;
			var = ft_substr(&str[*i + 1], 0, j);
			new_str = ft_join_var(control, ft_substr(str, 0, *i), var, &str[*i + 1
					+ j]);
			if (new_str != NULL)
			{
				free(str);
				str = NULL;
			}
			str = new_str;
			*i = 0;
		}
		return (str);
}

char	*get_var_in_quotes(t_control * control, int	*i, char *str)
{
	char	type_quote;
	
	type_quote = str[*i];
	if (type_quote == '\'')
	{
		*i = *i + 1;
		while (str[*i] && str[*i] != type_quote)
			*i = *i + 1;
	}
	if (type_quote == '"')
	{
		*i = *i + 1;
		while (str[*i] && str[*i] != type_quote)
		{
			str = expand_var(control, i, str);
			*i = *i + 1;
		}	
	}
	*i = *i + 1;
	return (str);			
}

char	*get_var_in_node(t_control *control, char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
			str = get_var_in_quotes(control, &i, str);
		else
		{
			str = expand_var(control, &i, str);
			if (*str)
				i++;
		}
		if (str[i] && set_type(str) != VAR_EXPAND)
			break;
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
		if (arg_node->type == VAR_EXPAND || look_exit_variabel(cmd, 0))
				arg_node->arg = get_var_in_node(control, arg_node->arg);
		arg_node = temp_arg_node;
	}
}

int	handle_expander(t_control *control)
{
	t_cmd	*cmd_node_temp;
	t_cmd	*cmd_node;

	cmd_node = control->cmd;
	while (cmd_node)
	{
		cmd_node_temp = cmd_node->next;
		if (cmd_node->type == VAR_EXPAND || look_exit_variabel(cmd_node, 1))
			cmd_node->cmd = get_var_in_node(control, cmd_node->cmd);
		get_var_in_arg(control, cmd_node);
		cmd_node = cmd_node_temp;
	}
	return (TRUE);
}

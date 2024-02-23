/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:10 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/23 20:33:49 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_join_var(int *i, char *str, char *var, char *end)
{
	char	*result;
	char	*temp;
	int		len;

	result = NULL;
	if (var)
	{
		temp = ft_strjoin(str, var);
		len = ft_strlen(temp);
		*i = len;
		result = ft_strjoin(temp, end);
		free(str);
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

int	is_exit_variable(char *str)
{
	if (str[0] && str[1] && str[0] == '$' && str[1] == '?')
		return (TRUE);
	return (FALSE);
}

int	look_exit_variabel(t_cmd *cmd, int flag)
{
	t_arg	*ptr_arg;
	int		i;

	i = 0;
	ptr_arg = cmd->list_args;
	if (flag)
	{
		while (cmd && cmd->cmd[i])
		{
			if (is_exit_variable(&cmd->cmd[i]))
				return (TRUE);
			i++;
		}
		return (FALSE);
	}
	i = 0;
	while (ptr_arg && ptr_arg->arg[i])
	{
		if (is_exit_variable(&ptr_arg->arg[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	is_variable(char *str)
{
	if (str[0] && str[1] && str[0] == '$' && ft_isdigit(str[1]))
		return (0);
	else if (str[0] && str[1] && str[0] == '$' && (ft_isalnum(str[1])
				|| str[1] == '_'))
		return (1);
	return (0);
}

void	set_path(t_control *control)
{
	char	*pwd;
	char	*temp_pwd;

	free(control->prompt);
	pwd = ft_strdup(get_var_env(control, "PWD"));
	temp_pwd = pwd;
	pwd = ft_strjoin("Minishell:", pwd);
	free(temp_pwd);
	control->prompt = ft_strjoin(pwd, " > ");
	free(pwd);
}

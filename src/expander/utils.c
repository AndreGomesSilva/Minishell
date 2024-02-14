/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:10 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/14 20:31:54 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_braces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '{')
		{
			if (str[i + 1] && ft_isdigit(str[i + 1]))
				return (FALSE);
			while (str[i])
			{
				if (str[i] == '{')
					return (FALSE);
				else if (str[i] == '}')
					return (TRUE);
				i++;
			}
		}	
		if (str[i])
			i++;
	}
	return (FALSE);
}

int	is_variable(char *str)
{
	if (str[0] && str[1] && str[0] == '$' && ft_isdigit(str[1]))
		return (0);
	else if (str[0] && str[1] && str[0] == '$' && (ft_isalnum(str[1])
			|| str[1] == '_' || valid_braces(&str[1])))
		return (1);
	return (0);
}

char	*convert_home_path(char *path, int len)
{
	char	*result;
	char	*sign;
	char	*cut_path;

	sign = ft_strdup("~");
	result = NULL;
	if (path)
	{
		cut_path = ft_substr(path, len, ft_strlen(path));
		result = ft_strjoin(sign, cut_path);
		free(cut_path);
		free(sign);
	}
	return (result);
}

char	*handle_home_path(t_control *control, char *path)
{
	int		i;
	char	*home;
	char	*new_path;

	i = 0;
	home = NULL;
	new_path = NULL;
	home = get_var(control, "HOME");
	while (path && path[i] && home[i])
	{
		if (!ft_strncmp(&path[i], &home[i], ft_strlen(home)))
		{
			new_path = convert_home_path(&path[i], (int)ft_strlen(home));
			return (new_path);
		}
		i++;
	}
	return (path);
}

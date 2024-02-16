/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:10 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/16 01:09:13 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_variable(char *str)
{
	if (str[0] && str[1] && str[0] == '$' && ft_isdigit(str[1]))
		return (0);
	else if (str[0] && str[1] && str[0] == '$' && (ft_isalnum(str[1])
			|| str[1] == '_'))
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
	home = get_var_env(control, "HOME");
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

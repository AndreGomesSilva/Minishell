/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:59 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/20 19:46:17 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_bin(char **split_path, char *cmd)
{
	char	*bin;
	char	*temp_path;
	int		i;

	i = 0;
	while (cmd && split_path[i])
	{
		temp_path = ft_strjoin(split_path[i], "/");
		bin = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!access(bin, X_OK))
			return (bin);
		free(bin);
		bin = NULL;
		i++;
	}
	return (bin);
}

char	*get_cmd_path(t_control *control, char *cmd)
{
	char	*path_var;
	char	*bin;
	char	**split_path;

	bin = NULL;
	path_var = get_var_env(control, "PATH");
	if (path_var)
	{
		split_path = ft_split(path_var, ':');
		bin = get_bin(split_path, cmd);
		free_matrix(split_path);
	}
	return (bin);
}

char	*handle_bin_path(t_control *control, char *cmd)
{
	char	*bin_path;

	bin_path = NULL;
	if (is_absolute_path(cmd))
		bin_path = ft_strdup(cmd);
	else if (!is_builtin(cmd))
		bin_path = get_cmd_path(control, cmd);
	return (bin_path);
}

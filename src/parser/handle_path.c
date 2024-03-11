/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:59 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/11 17:38:23 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_bin(char **split_path, char *cmd)
{
	char	*bin;
	char	*temp_path;
	int		i;

	i = 0;
	bin = NULL;
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

char	*handle_bin_path(t_control *control, char **cmd)
{
	char	*bin_path;
	char	*path_var;
	char	**split_path;

	path_var = get_var_env(control, "PATH");
	bin_path = NULL;
	if (is_a_directory(*cmd))
		bin_path = ft_strdup(*cmd);
	else if (!is_builtin(*cmd))
	{
		if (path_var)
		{
			split_path = ft_split(path_var, ':');
			bin_path = get_bin(split_path, *cmd);
			free_matrix(split_path);
		}
		else
			*cmd = swap_string(ft_strdup("./"), *cmd);
	}
	return (bin_path);
}

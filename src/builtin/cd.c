/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/15 23:17:19 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_cd(t_control *control, char **cmd)
{
	char		*pwd_relative;
	char		*pwd;
	const char	*old_pwd = getcwd(NULL, 0);

	if (cmd[2])
		print_simple_error("CD");
	else
		ft_putendl_fd(getcwd(NULL, 0), 1);
	if (chdir(cmd[1]) == 0)
	{
		update_env(control, "OLDPWD", old_pwd);
		update_env(control, "PWD", getcwd(NULL, 0));
	}
	pwd = getcwd(NULL, 0);
	pwd_relative = ft_strjoin((const char *)pwd, (const char *)cmd[1]);
	if (chdir(pwd_relative) == 0)
	{
		update_env(control, "OLDPWD", old_pwd);
		update_env(control, "PWD", getcwd(NULL, 0));
		free(pwd_relative);
	}
}

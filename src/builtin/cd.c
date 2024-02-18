/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/18 02:31:25 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	check_pwd_exist(t_control *control, char *pwd_relative, const char *old_pwd,
		char *pwd)
{
	if (chdir(pwd_relative) == 0)
	{
		update_env(control, "OLDPWD", old_pwd);
		update_env(control, "PWD", pwd);
		free(pwd);
		free(pwd_relative);
		return (TRUE);
	}
	else
	{
		free(pwd);
		free(pwd_relative);
		return (FALSE);
	}
}

void	handle_cd_builtin(t_control *control, char **cmd)
{
	char		*pwd_relative;
	char		*pwd;
	const char	*old_pwd = getcwd(NULL, 0);
	int			result_relative;

	if (!cmd[1])
		return ;
	if (chdir(cmd[1]) == 0)
	{
		update_env(control, "OLDPWD", old_pwd);
		update_env(control, "PWD", getcwd(NULL, 0));
		printf("%s", get_var_env(control, "PWD"));
		set_path(control);
		return ;
	}
	pwd = getcwd(NULL, 0);
	pwd_relative = ft_strjoin((const char *)pwd, (const char *)cmd[1]);
	result_relative = check_pwd_exist(control, pwd_relative, old_pwd, pwd);
	if (result_relative)
	{
		printf("%s", get_var_env(control, "PWD"));	
		set_path(control);
	}
	else
		print_simple_error("CD_NO_EXIST");
}

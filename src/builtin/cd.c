/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/25 23:16:49 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pwd_exist(t_control *control, char *pwd_relative, const char *old_pwd,
		char *pwd)
{
	if (chdir(pwd_relative) == 0)
	{
		update_env(control, ft_strdup("OLDPWD"), old_pwd, FALSE);
		update_env(control, ft_strdup("PWD"), pwd, FALSE);
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

	if ((!cmd[1] && !chdir(get_var_env(control, "HOME"))) || !chdir(cmd[1]))
	{
		update_env(control, ft_strdup("OLDPWD"), old_pwd, FALSE);
		update_env(control, ft_strdup("PWD"), getcwd(NULL, 0), FALSE);
		set_path(control);
		return ;
	}
	pwd = getcwd(NULL, 0);
	pwd_relative = ft_strjoin((const char *)pwd, (const char *)cmd[1]);
	result_relative = check_pwd_exist(control, pwd_relative, old_pwd, pwd);
	if (result_relative)
		set_path(control);
	else
	{
		printf("%s%s%s\n", "cd: ", cmd[1], ": No such file or directory");
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
	}
}

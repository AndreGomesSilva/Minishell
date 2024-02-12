/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 20:02:24 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*make_cd(t_control *control, char *pwd_target)
{
	char		*pwd_relative;
	char		*pwd;
	const char	*old_pwd = getcwd(NULL, 0);

	if (chdir(pwd_target) == 0)
	{
		update_env(control, "OLDPWD", old_pwd);
		update_env(control, "PWD", getcwd(NULL, 0));
		return (getcwd(NULL, 0));
	}
	pwd = getcwd(NULL, 0);
	pwd_relative = ft_strjoin((const char *)pwd, (const char *)pwd_target);
	if (chdir(pwd_relative) == 0)
	{
		update_env(control, "OLDPWD", old_pwd);
		update_env(control, "PWD", getcwd(NULL, 0));
		free(pwd_relative);
		return (getcwd(NULL, 0));
	}
	return (FALSE);
}

int	handle_cd(t_control *control, char *cmd)
{
	char	*result;

	result = make_cd(control, cmd);
	if (!result)
		return (FALSE);
	free(result);
	return (TRUE);
}

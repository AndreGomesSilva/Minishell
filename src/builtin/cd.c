/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/03 20:11:32 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pwd_exist(t_control *control, char *pwd_relative, char *old_pwd,
		char *pwd)
{
	if (chdir(pwd_relative) == 0)
	{
		update_env(control, ft_strdup("OLDPWD"), old_pwd, FALSE);
		update_env(control, ft_strdup("PWD"), pwd, FALSE);
		free(pwd_relative);
		return (TRUE);
	}
	else
	{
		free(old_pwd);
		free(pwd);
		free(pwd_relative);
		return (FALSE);
	}
}

int	check_many_params(char **cmd, t_control *control, char *old_pwd)
{
	char	*error_message;

	if (cmd && cmd[1] && cmd[2])
	{
		error_message = swap_string(ft_strdup("cd: "),
				ft_strdup("': too many arguments\n"));
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
		ft_putstr_fd(error_message, 2);
		free(error_message);
		free(old_pwd);
		return (TRUE);
	}
	return (FALSE);
}

static void	print_error_message(char **cmd, int i)
{
	char	*error_message;

	error_message = swap_string(ft_strdup("cd: "), ft_strdup(cmd[i]));
	error_message = swap_string(error_message,
			ft_strdup(": No such file or directory\n"));
	ft_putstr_fd(error_message, 2);
	free(error_message);
}

void	handle_cd_builtin(t_control *control, char **cmd)
{
	char		*pwd_relative;
	char		*pwd;
	char		*old_pwd;
	int			result_relative;

	old_pwd = getcwd(NULL, 0);
	if (check_many_params(cmd, control, old_pwd))
		return ;
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
		print_error_message(cmd, 1);
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
	}
}

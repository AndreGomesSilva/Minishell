/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/07 14:49:56 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pwd_exist(t_control *control, char *pwd_relative, char **old_pwd,
		char *pwd)
{
	int	result_chdir;
	int	return_value;

	result_chdir = chdir(pwd_relative);
	return_value = 1;
	if (result_chdir == 0)
	{
		update_env(control, ft_strdup("OLDPWD"), *old_pwd, FALSE);
		update_env(control, ft_strdup("PWD"), pwd, FALSE);
		free(pwd_relative);
		return (return_value);
	}
	else
	{
		if (!access(pwd_relative, F_OK) && (access(pwd_relative, R_OK
					|| access(pwd_relative, X_OK))))
			return_value = -1;
		else
			return_value = 0;
		free(*old_pwd);
		free(pwd);
		free(pwd_relative);
		return (return_value);
	}
}

int	check_many_params(char **cmd, t_control *control, char **old_pwd)
{
	char	*error_message;

	*old_pwd = getcwd(NULL, 0);
	if (!*old_pwd)
		*old_pwd = ft_strdup(get_var_env(control, "PWD"));
	if (cmd && cmd[1] && cmd[2])
	{
		error_message = swap_string(ft_strdup("cd: "),
				ft_strdup("too many arguments\n"));
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
		ft_putstr_fd(error_message, 2);
		free(error_message);
		free(*old_pwd);
		return (TRUE);
	}
	return (FALSE);
}

void	print_error_message(char **cmd, int i, int type)
{
	char	*error_message;

	if (type == 1)
	{
		error_message = swap_string(ft_strdup("cd: "), ft_strdup(cmd[i]));
		error_message = swap_string(error_message,
				ft_strdup(": No such file or directory\n"));
	}
	else if (type == 2)
	{
		error_message = swap_string(ft_strdup("cd: "), ft_strdup(cmd[i]));
		error_message = swap_string(error_message,
				ft_strdup(": Permission denied\n"));
	}
	else if (type == 3)
		error_message = ft_strdup("cd: No such file or directory \n");
	else
		error_message = ft_strdup("cd: HOME not set \n");
	ft_putstr_fd(error_message, 2);
	free(error_message);
}

void	check_pwd_relative(char **cmd, t_control *control, char **old_pwd)
{
	char	*pwd;
	char	*pwd_relative;
	int		result_relative;

	pwd = getcwd(NULL, 0);
	pwd_relative = ft_strjoin(pwd, "/");
	pwd_relative = swap_string(pwd_relative, ft_strdup(cmd[1]));
	result_relative = check_pwd_exist(control, pwd_relative, old_pwd, pwd);
	if (result_relative == 1 && set_path(control))
		return ;
	else if (result_relative == -1)
		print_error_message(cmd, 1, 2);
	else if (result_relative == 0)
		print_error_message(cmd, 1, 1);
	update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
}

void	handle_cd_builtin(t_control *control, char **cmd)
{
	char	*old_pwd;

	if (!get_var_env(control, "HOME"))
	{
		print_error_message(cmd, 1, 4);
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
		return ;
	}
	if (check_many_params(cmd, control, &old_pwd))
		return ;
	else if ((!cmd[1] && !chdir(get_var_env(control, "HOME")))
		|| !chdir(cmd[1]))
	{
		update_env(control, ft_strdup("OLDPWD"), old_pwd, FALSE);
		update_env(control, ft_strdup("PWD"), getcwd(NULL, 0), FALSE);
		set_path(control);
	}
	else if (ft_strncmp(cmd[1], "/", 2))
	{
		print_error_message(cmd, 1, 3);
		update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
		free(old_pwd);
	}
	else
		check_pwd_relative(cmd, control, &old_pwd);
}

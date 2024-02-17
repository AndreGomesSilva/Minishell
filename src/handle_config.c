/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/17 16:33:57 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_path(t_control *control)
{
	char	*pwd;
	char	*user;
	char	*temp_pwd;
	char	*temp_user;
	
	pwd = get_var_env(control, "PWD");
	user = get_var_env(control, "USER");
	if (pwd)
			pwd = handle_home_path(control, pwd);
	if (user)
		control->user = user;
	else
		control->user = ft_strdup("GUEST");
	temp_user = ft_strjoin(control->user, "@Minishell:");
	temp_pwd = ft_strjoin(temp_user, pwd);
	control->prompt = ft_strjoin(temp_pwd, "$ ");
	free(pwd);
	free(temp_user);
	free(temp_pwd);
}

int	handle_envp(t_control *control, char **env)
{
	t_table	*table;

	table = init_table(env);
	control->env_table = table;
	copy_env(control, env);
	return (TRUE);
}

void	handle_config(t_control **control, char **env)
{
	*control = (t_control *)ft_calloc(sizeof(t_control), 1);
	handle_envp(*control, env);
	set_path(*control);
}

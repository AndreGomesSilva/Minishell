/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/18 14:22:42 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

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
	char	*pwd;
	char	*temp_pwd;

	*control = (t_control *)ft_calloc(sizeof(t_control), 1);
	handle_envp(*control, env);
	pwd = getcwd(NULL, 0);
	temp_pwd = pwd;
	pwd = ft_strjoin("Minishell:", pwd);
	free(temp_pwd);
	(*(control))->prompt = ft_strjoin(pwd, " > ");
	free(pwd);
}

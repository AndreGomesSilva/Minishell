/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/02 15:50:36 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_envp(t_control *control, char **env)
{
	t_table	*table;

	table = init_table(env);
	control->env_table = table;
	copy_env(control, env);
	update_matrix_env(control);
	update_env(control, ft_strdup("?"), ft_strdup("0"), FALSE);
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

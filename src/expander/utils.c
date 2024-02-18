/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:16:10 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/18 02:33:51 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_variable(char *str)
{
	if (str[0] && str[1] && str[0] == '$' && ft_isdigit(str[1]))
		return (0);
	else if (str[0] && str[1] && str[0] == '$' && (ft_isalnum(str[1])
			|| str[1] == '_'))
		return (1);
	return (0);
}

void	set_path(t_control *control)
{
	char	*pwd;
	char	*temp_pwd;
	
	free(control->prompt);
	pwd = ft_strdup(get_var_env(control, "PWD"));
	temp_pwd = pwd;
	pwd = ft_strjoin("Minishell:", pwd);
	free(temp_pwd);
	control->prompt = ft_strjoin(pwd, " > ");
	free(pwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/07 22:51:45 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_echo(char **cmd)
{
	
}

// TODO: corrigir entrada por matriz e testar
int	handle_cd(char **matriz)
{
	char	*pwd_relative;
	char	*pwd;

	if (chdir(pwd_target) != 0)
	{
		pwd = getcwd(NULL, NULL);
		pwd_relative = ft_strjoin((const char *)pwd, (const char *)pwd_target);
		free(pwd);
		if (chdir(pwd_relative) != 0)
		{
			free(pwd_relative);
			return (FALSE);
		}
		else
		{
			free(pwd_relative);
			return (TRUE);
		}
	}
	return (TRUE);
}

int	handle_pwd(char **cmd)
{
	
}

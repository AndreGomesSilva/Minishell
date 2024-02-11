/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/11 00:26:34 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*make_cd(char *pwd_target)
{
	char		*pwd_relative;
	char		*pwd;

	if (chdir(pwd_target) == 0)
		return (getcwd(NULL, 0));
	
	pwd = getcwd(NULL, 0);
	pwd_relative = ft_strjoin((const char *)pwd, (const char *)pwd_target);
	if(chdir(pwd_relative) == 0)
	{
		free(pwd_relative);
		return (getcwd(NULL, 0));
	}	
	return (FALSE);
}

int	handle_builtin_cd(char *cmd)
{
	char *result;

	result = make_cd(cmd);
	if(!result)
		return (FALSE);
	free(result);
	return (TRUE);	
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:59:43 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/06 23:50:27 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: make_cd.
int	make_cd(char *pwd_target, t_control *control)
{
	char *pwd_relative;
	char *error_msg;
	char *temp;

	pwd_relative = ft_strjoin((const char *)control->pwd,
			(const char *)pwd_target); 
	if (access(pwd_relative, F_OK) != -1)
	{
		free(control->pwd);
		control->pwd = pwd_relative;
	}
	else 
	{
		error_msg = ft_strjoin("cd: ", pwd_target);
		temp = error_msg;
		error_msg = ft_strjoin(error_msg, ": No such file or directory");
		free(temp);
		temp = error_msg;
		error_msg = ft_strjoin(error_msg, "\n");
		ft_putstr_fd(error_msg, 2);
		free(temp);
		free(error_msg);
	}

	// 2- verifico se caminho alvo existe.
	// 	2.1- Existe ? access para verificar. E mudo o pwd da estrutura
	// 	2.1- Não existe? Retorno erro.

	// const char *path = "/caminho/para/verificar";
}

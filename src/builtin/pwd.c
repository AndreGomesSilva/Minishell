/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:32:57 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/25 19:57:47 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_pwd_builtin(t_control *control)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free((char *)cwd);
	}
	else
	{
		perror("pwd");
		update_env(control, ft_strdup("?"), ft_strdup("1"));
	}
}

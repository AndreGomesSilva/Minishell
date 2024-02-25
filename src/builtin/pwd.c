/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:32:57 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/24 19:41:27 by r-afonso         ###   ########.fr       */
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
		update_env(control, "?", ft_strdup("1"));
	}
}

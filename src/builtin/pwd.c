/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:32:57 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/16 01:08:01 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_pwd_builtin(t_control *control, char **cmd)
{
	if(cmd[1])
		print_simple_error("PWD");
	else
		ft_putendl_fd(get_var_env(control, "PWD"), 1);
}

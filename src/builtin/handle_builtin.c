/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:49:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/15 23:21:01 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtin(char **cmd, int fd, t_control *control)
{
	enum e_type_builtin	builtin;

	builtin = is_builtin(cmd[0]);
	if (builtin == B_CD || builtin == B_ECHO || builtin == B_EXPORT
		|| builtin == B_UNSET || builtin == B_ENV || builtin == B_EXIT
		|| builtin == B_PWD)
	{
		if (builtin == B_CD)
			handle_cd_builtin(control, cmd);
		else if (builtin == B_ECHO)
			handle_echo_builtin(cmd, fd);
		else if (builtin == B_EXIT)
			handle_exit_builtin(control);
		else if (builtin == B_ENV)
			handle_env_builtin(control);
		else if (builtin == B_EXPORT)
			handle_export_builtin(control, cmd);
		else if (builtin == B_UNSET)
			handle_unset_builtin(control, cmd);
		else if (builtin == B_EXIT)
			handle_pwd_builtin(control, cmd);
		return (TRUE);
	}
	return (FALSE);
}

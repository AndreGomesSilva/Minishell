/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:49:12 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/07 17:27:21 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtin(char **cmd, t_control *control)
{
	const enum e_type_builtin	builtin = is_builtin(cmd[0]);

	if (builtin == B_CD || builtin == B_ECHO || builtin == B_EXPORT
		|| builtin == B_UNSET || builtin == B_ENV || builtin == B_EXIT
		|| builtin == B_PWD)
	{
		if (builtin != B_ECHO && builtin != B_EXIT)
			update_env(control, ft_strdup("?"), ft_strdup("0"), FALSE);
		if (builtin == B_CD)
			handle_cd_builtin(control, cmd);
		else if (builtin == B_ECHO)
			handle_echo_builtin(control, cmd);
		else if (builtin == B_EXIT)
			handle_exit_builtin(control, cmd);
		else if (builtin == B_ENV)
			handle_env_builtin(control, cmd);
		else if (builtin == B_EXPORT)
			handle_export_builtin(control, cmd);
		else if (builtin == B_UNSET)
			handle_unset_builtin(control, cmd);
		else if (builtin == B_PWD)
			handle_pwd_builtin(control);
		return (TRUE);
	}
	return (FALSE);
}

int	is_valid_env_name(char *str)
{
	int			i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && str[i] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

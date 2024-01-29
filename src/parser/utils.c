//
// Created by angomes- on 1/29/24.
//

#include "../../include/minishell.h"

int is_builtin(char *cmd)
{
	int len;

	if (!cmd)
		return (FALSE);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", len))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", len))
		return (PWD);
	else if (!ft_strncmp(cmd, "env", len))
		return (ENV);
	else if (!ft_strncmp(cmd, "export", len))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", len))
		return (UNSET);
	return (NOBT);
}
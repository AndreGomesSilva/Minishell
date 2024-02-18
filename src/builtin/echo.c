/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:32:36 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/18 14:33:16 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*build_output_string(char **cmd, int *new_line)
{
	int		i;
	char	*buffer;
	char	*temp;

	if (ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		*new_line = 0;
		buffer = ft_strdup(cmd[2]);
		i = 2;
	}
	else
	{
		buffer = ft_strdup(cmd[1]);
		i = 1;
	}
	while (i++, cmd[i])
	{
		temp = buffer;
		buffer = ft_strjoin(buffer, " ");
		free(temp);
		temp = buffer;
		buffer = ft_strjoin(buffer, cmd[i]);
		free(temp);
	}
	return (buffer);
}

void	handle_echo_builtin(t_control *control, char **cmd)
{
	int		new_line;
	char	*output_string;

	if(!cmd[1])
		return ;
	(void) control;
	new_line = 1;
	output_string = build_output_string(cmd, &new_line);
	printf("%s", output_string);
	if (new_line)
		printf("\n");
	free(output_string);
}

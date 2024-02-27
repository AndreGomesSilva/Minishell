/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:32:36 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/27 13:44:21 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_new_line(char **cmd, int position, int *new_line)
{
	if (ft_strncmp(cmd[position], "-n", 3) == 0)
	{
		*new_line = 0;
		return (1);
	}
	return (0);
}

char	*build_output_string(char **cmd, int *new_line)
{
	char	*buffer;
	char	*temp;
	int		position;

	position = 1;
	while (check_new_line(cmd, position, new_line))
		position++;
	if (cmd[position])
		buffer = ft_strdup(cmd[position]);
	while (position++, cmd[position])
	{
		temp = buffer;
		buffer = ft_strjoin(buffer, " ");
		free(temp);
		temp = buffer;
		buffer = ft_strjoin(buffer, cmd[position]);
		free(temp);
	}
	return (buffer);
}

void	handle_echo_builtin(t_control *control, char **cmd)
{
	int		new_line;
	char	*output_string;

	if (!cmd[1])
		return ;
	(void)control;
	new_line = 1;
	output_string = build_output_string(cmd, &new_line);
	printf("%s", output_string);
	if (new_line)
		printf("\n");
	update_env(control, ft_strdup("?"), ft_strdup("0"), FALSE);
	free(output_string);
}

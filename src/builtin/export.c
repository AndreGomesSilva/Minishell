/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:33:15 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/21 22:51:556 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_valid(int i, int position_equal, char **cmd, t_control *control)
{
	if (position_equal != -1)
		update_env(control, ft_substr(cmd[i], 0, position_equal),
				ft_substr(cmd[i], position_equal + 1, ft_strlen(cmd[i])
					- position_equal - 1), FALSE);
	else
		update_env(control, ft_substr(cmd[i], 0, position_equal), ft_strdup(""),
				TRUE);
}

static void	print_error_message(char **cmd, int i)
{
	char	*error_message;

	error_message = swap_string(ft_strdup("export: `"), ft_strdup(cmd[i]));
	error_message = swap_string(error_message,
								ft_strdup("': not a valid identifier\n"));
	ft_putstr_fd(error_message, 2);
	free(error_message);
}
void	handle_export_builtin(t_control *control, char **cmd)
{
	int		i;
	int		position_equal;
	char	*str;

	i = 0;
	if (!cmd[1])
	{
		print_sort_env(control);
		return ;
	}
	while (i++, cmd[i])
	{
		position_equal = get_size_env_key(cmd[i]);
		str = ft_substr(cmd[i], 0, position_equal);
		if (is_valid_env_name(str) && position_equal != 0)
			export_valid(i, position_equal, cmd, control);
		else
		{
			print_error_message(cmd, i);
			update_env(control, ft_strdup("?"), ft_strdup("1"), FALSE);
		}
		free(str);
	}
}

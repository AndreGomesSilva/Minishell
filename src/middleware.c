/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:41 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 17:20:45 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	middleware(t_control *control)
{
	char	*input;
	char	*first_input;

	input = readline(control->prompt);
	first_input = input;
	if (input)
	{
		add_history(input);
		while (is_space(*input))
			input++;
		if (*input)
			handle_token(control, input);
		handle_heredoc(control);
		if (handle_expander(control))
			if (handle_parser(control))
				handle_execution(control);
		print_lst(control->cmd);
		free(first_input);
		free_cmd(control);
		return (TRUE);
	}
	else
		receive_signal_ctrl_d(control);
	return (FALSE);
}

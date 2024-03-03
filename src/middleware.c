/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:41 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/02 16:51:57 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	middleware(t_control *control, char *input)
{
	handle_token(control, input);
	control->fatal_err = verify_broken_quote(control);
	if (!control->fatal_err)
	{
		if (handle_heredoc(control) == FALSE)
			return ;
		handle_expander(control);
		handle_parser(control);
	}
	handle_execution(control);
}

void	get_input(t_control *control)
{
	char	*input;

	input = readline(control->prompt);
	control->first_input = input;
	if (input)
	{
		if (*input)
		{
			add_history(input);
			while (is_space(*input))
				input++;
			if (*input)
				middleware(control, input);
			free(control->first_input);
			free_cmd(control);
		}
	}
	else
		receive_signal_ctrl_d(control);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:41 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/27 18:07:51 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	middleware(t_control *control, char *input)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = NULL;
	handle_token(control, input);
	control->fatal_err = verify_broken_quote(control);
	if (!control->fatal_err)
	{
		if (handle_heredoc(control) == FALSE)
			return ;
		handle_expander(control);
		handle_parser(control, ptr_cmd);
	}
	handle_execution(control);
}

void	get_input(t_control *control)
{
	char	*input;
	char	*first_input;

	input = readline(control->prompt);
	first_input = input;
	if (input)
	{
		if (*input)
		{
			add_history(input);
			while (is_space(*input))
				input++;
			if (*input)
				middleware(control, input);
			free(first_input);
			free_cmd(control);
		}
	}
	else
		receive_signal_ctrl_d(control);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:41 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/23 21:48:12 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	middleware(t_control *control, char *input)
{
	handle_token(control, input);
	control->fatal_err = verify_broken_quote(control);
	if (!control->fatal_err)
	{
		update_env(control, "?", ft_strdup("0"));
		handle_heredoc(control);
		if (ft_atoi(get_var_env(control, "?")) == 130)
			return ;
		handle_expander(control);
		handle_parser(control);
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

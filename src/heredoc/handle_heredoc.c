/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:09:04 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/06 01:13:35 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_heredoc_expand_var(t_control *control, char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
		input = expand_var(control, &i, input);
	return (input);
}

int	get_input_heredoc(t_control *control, t_cmd *cmd, char *eof, int *action)
{
	int		flux_ctrl;
	char	*new_eof;
	char	*input;

	input = readline("> ");
	flux_ctrl = 0;
	if (input)
	{
		new_eof = remove_quotes(eof);
		flux_ctrl = str_compare(new_eof, input);
		if (flux_ctrl)
		{
			add_history(input);
			if (handle_quote_eof(eof) == NORM)
				input = get_heredoc_expand_var(control, input);
			*action = create_heredoc_file(cmd, input, action);
		}
		free(input);
		free(new_eof);
	}
	else if (ft_atoi(get_var_env(control, "?")) == 130)
		flux_ctrl = 0;
	else
		print_error_heredoc(eof);
	return (flux_ctrl);
}

void	ctrl_flux_heredoc(t_control *control, t_cmd *cmd, char *eof,
		int *action)
{
	int	flux_ctrl;
	int	old_stdin;

	flux_ctrl = 1;
	signal(SIGINT, ctrl_c_heredoc);
	old_stdin = dup(STDIN_FILENO);
	while (flux_ctrl && ft_atoi(get_var_env(control, "?")) != 130)
	{
		if (ft_atoi(get_var_env(control, "?")) == 130)
			break ;
		flux_ctrl = get_input_heredoc(control, cmd, eof, action);
		if (!cmd->heredoc_file)
			cmd->error_type = E_CTRL_D_HERE;
	}
	if (ft_atoi(get_var_env(control, "?")) == 130)
	{
		control->status_cmd = 130;
		dup2(old_stdin, STDIN_FILENO);
	}
	close(old_stdin);
}

void	open_prompt(t_control *control, t_cmd *cmd)
{
	int		action;
	char	*eof;

	if (ft_atoi(get_var_env(control, "?")) == 130)
		update_env(control, ft_strdup("?"), ft_strdup("0"), FALSE);
	eof = get_next_eof(cmd);
	action = 0;
	while (eof)
	{
		ctrl_flux_heredoc(control, cmd, eof, &action);
		action = 0;
		eof = get_next_eof(cmd);
	}
}

int	handle_heredoc(t_control *control)
{
	t_cmd	*ptr_cmd;
	t_cmd	*next_cmd;

	ptr_cmd = control->cmd;
	control->status_cmd = 0;
	while (ptr_cmd && !handle_syntax_error_heredoc(ptr_cmd))
	{
		next_cmd = ptr_cmd->next;
		if (find_heredoc_cmd(ptr_cmd))
			open_prompt(control, ptr_cmd);
		ptr_cmd = next_cmd;
	}
	if (control->status_cmd != 0)
		return (FALSE);
	return (TRUE);
}

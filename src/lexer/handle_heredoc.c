/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:11:45 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/23 22:27:13y angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_heredoc_file(t_cmd *cmd, char *input, int *action)
{
	int		fd;
	char	*name;
	char	*file;

	name = ft_itoa(cmd->cmd_number);
	file = ft_strjoin("/tmp/", name);
	if (*action == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		print_error(cmd, E_NO_FILE);
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
	if (cmd->heredoc_file)
	{
		free(cmd->heredoc_file);
		cmd->heredoc_file = file;
	}
	else
		cmd->heredoc_file = file;
	free(name);
	return (TRUE);
}

int	get_input_heredoc(t_control *control, t_cmd *cmd, char *eof, int *action)
{
	int		flux_ctrl;
	char	*new_eof;
	char	*input;

	input = readline("> ");
	if (input)
	{
		new_eof = remove_quotes(eof);
		flux_ctrl = str_compare(new_eof, input);
		if (flux_ctrl)
		{
			add_history(input);
			if (handle_quote_eof(eof) == NORM)
				input = get_var_in_node(control, input);
			*action = create_heredoc_file(cmd, input, action);
		}
		free(input);
		free(new_eof);
	}
	else if (ft_atoi(get_var_env(control, "?")) == 130)
			return (0);
	else	
		flux_ctrl = ctrl_d_herdoc(control, remove_quotes(eof));
	return (flux_ctrl);
}

void	ctrl_flux_heredoc(t_control *control, t_cmd *cmd, char *eof, int *action)
{
	int		flux_ctrl;
	int		old_stdin;

	flux_ctrl = 1;
	signal(SIGINT, ctrl_c_heredoc);
	old_stdin = dup(STDIN_FILENO);
	while (flux_ctrl && ft_atoi(get_var_env(control, "?")) != 130)
	{
		if (ft_atoi(get_var_env(control, "?")) == 130)
			break;
		flux_ctrl = get_input_heredoc(control, cmd, eof, action);
	}
	if (ft_atoi(get_var_env(control, "?")) == 130)
	{
		control->status_heredoc = 130;
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
	control->status_heredoc  = 0;
	while (ptr_cmd)
	{
		next_cmd = ptr_cmd->next;
		if (find_heredoc_cmd(ptr_cmd))
			open_prompt(control, ptr_cmd);
		ptr_cmd = next_cmd;
	}
	if (control->status_heredoc == 130)
			return (FALSE);
	return (TRUE);	
}

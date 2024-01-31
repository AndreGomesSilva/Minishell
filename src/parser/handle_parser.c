#include "../../include/minishell.h"

// void	type_io_file(t_control *control)
// {
//	t_cmd *ptr_cmd;
//	t_arg *ptr_arg;
//
//	ptr_cmd = control->cmd;
//	ptr_arg = ptr_cmd->list_args;
//	while (ptr_cmd)
//	{
//		if (ptr_cmd->type == REDIRECT_INPUT && ptr_arg)
//			ptr_arg->type = INFILE;
//		else if (ptr_cmd->type == REDIRECT_HERD && ptr_arg)
//			ptr_arg->type = INFILE;
//		else if (ptr_cmd->type == REDIRECT_OUTPUT && ptr_arg)
//			ptr_arg->type = OUTFILE;
//
//		ptr_cmd = ptr_cmd->next;
//	}
// }

// int	count_args(t_cmd *cmd)
// {
//	int count;
//	t_cmd *ptr_cmd;
//	t_arg *ptr_arg;
//
//	ptr_cmd = cmd;
//	ptr_arg = ptr_cmd->list_args;
//	count = 0;
//	if (ptr_cmd->type < REDIRECT_HERD)
//		count++;
//	while (ptr_arg)
//	{
//		if (ptr_arg->type < REDIRECT_HERD)
//			count++;
//		ptr_arg = ptr_arg->next;
//	}
//	if (count < 0)
//		return (0);
//	return (count);
// }
//
// char	**create_full_cmd(t_control *control)
// {
//	int		len;
//	char	**args;
//	int 	i;
//	t_cmd *ptr_cmd;
//	t_arg *ptr_arg;
//
//	ptr_cmd = control->cmd;
//	ptr_arg = ptr_cmd->list_args;
//	i = 0;
//	while (ptr_cmd)
//	{
//		len = count_args(ptr_cmd);
//		args = (char **)ft_calloc(len, sizeof(char **));
//		if (ptr_cmd->type < REDIRECT_HERD)
//			args[i++] = ft_strdup(ptr_cmd->cmd);
//		while (ptr_arg)
//		{
//			if (ptr_arg->type < REDIRECT_HERD)
//				args[i++] = ft_strdup(ptr_arg->arg);
//			ptr_arg = ptr_arg->next;
//		}
//		ptr_cmd->cmd_and_args = args;
//		ptr_cmd = ptr_cmd->next;
//	}
//	return (args);
// }
//
 void	handle_parser(t_control *control)
 {
	 handle_bin_path(control, control->cmd);
//	 create_full_cmd(control);
 }

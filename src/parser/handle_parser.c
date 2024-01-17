#include "../../include/minishell.h"

// int	count_valid_args(t_cmd *cmd)
// {
// 	int 	count;
// 	t_arg	*node_arg;
// 	t_arg 	*temp_node_arg;

// 	count = 0;
// 	node_arg = cmd->list_args;
// 	if (cmd->cmd)
// 		count++;
// 	while (node_arg)
// 	{
// 		temp_node_arg = node_arg->next;
// 		while (node_arg->arg)
// 			count++;
// 		node_arg = temp_node_arg;
// 	}
// 	return (count);
// }

// char **create_cmd_matrix(t_cmd *cmd)
// {
// 	char	**matrix;
// 	int		number_args;
// 	int 	i;
// 	int 	j;

// 	i = 0;
// 	number_args = count_valid_args(cmd);
// 	matrix = (char**) ft_calloc(number_args + 1, sizeof(char**));
// 	if (!matrix)
// 		return (NULL);
// 	while(matrix[i])
// 	{
// 		j = 0;
// 		while (matrix[i][j])
// 		{
// 		}
// 		i++;
// 	}
// 	return (matrix);
// }

// void	get_cmd_matrix(t_control *control)
// {
// 	t_cmd *cmd;
// 	t_cmd *temp_cmd;

// 	cmd = control->cmd;
// 	while (cmd)
// 	{
// 		cmd->cmd_and_args = create_cmd_matrix(cmd);
// 		cmd = cmd->next;
// 	}
// }

void	handle_parser(t_control *control)
{
	// get_cmd_matrix(control);
}

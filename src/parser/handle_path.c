//
// Created by angomes- on 1/30/24.
//

#include "../../include/minishell.h"

char *get_bin(char **split_path, char *cmd)
{
	char *bin;
	char *temp_path;
	int i;

	i = 0;
	while (cmd && split_path[i])
	{
		temp_path = ft_strjoin(split_path[i], "/");
		bin = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!access(bin, X_OK))
			return (bin);
		free(bin);
		bin = NULL;
		i++;
	}
	return (bin);
}

char *get_cmd_path(t_control *control, t_cmd *cmd)
{
	char *path_var;
	char *bin;
	char **split_path;
	int	 i;


	i = 0;
	bin = NULL;
	path_var = get_var(control, "PATH");
	if (path_var)
	{
		split_path = ft_split(path_var, ':');
		bin = get_bin(split_path, cmd->cmd);
		free_matrix(split_path);
	}
	return (bin);
}

void handle_bin_path(t_control *control, t_cmd *cmd)
{
	t_cmd *ptr_cmd;
	ptr_cmd = cmd;

	if (is_builtin(ptr_cmd->cmd))
		ptr_cmd->path_cmd = NULL;
	else
		ptr_cmd->path_cmd = get_cmd_path(control, ptr_cmd);
}
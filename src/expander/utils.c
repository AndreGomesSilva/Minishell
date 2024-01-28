//
// Created by angomes on 13/01/24.
//

#include "../../include/minishell.h"

int is_variable(char *str)
{
	if (str[0] && str[1] && str[0] == '$' && (ft_isalpha(str[1]) || str[1] == '_'))
		return (1);
	return (0);
}

char	*convert_home_path(char *path, int len)
{
	char *result;
	char *sinal;
	char *cut_path;

	sinal = ft_strdup("~");
	if (path)
	{
		cut_path = ft_substr(path, len, ft_strlen(path));
		result = ft_strjoin(sinal, cut_path);
		free(cut_path);
		free(sinal);
	}
	return (result);
}

char *handle_home_path(t_control *control, char *path)
{
	int	i;
	char *home;
	char *new_path;
	
	i = 0;
	home = NULL;
	new_path = NULL;
	home = get_var(control, "HOME");
	while (path[i] && home[i])
	{
		if (!ft_strncmp(&path[i], &home[i], ft_strlen(home)))
		 {
			new_path = convert_home_path(&path[i], ft_strlen(home));
			return (new_path);
		 }
		 i++;
	}
	return (path);
}
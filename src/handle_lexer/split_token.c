#include "../../include/minishell.h"

int	is_args(t_control *control, char *input)
{
}

//0 = false, 1 = pipe, 2 = or, 3 = and
int	is_cmd(char *input)
{
	char	*str;
	int		i;

	str = input;
	i = 0;
	if (!str || !*str)
		return (NILL);
	else if (str[i] == '|')
		if (str[i + 1] == '|')
			return (OR);
		else
			return (PIP);
	else if (str[i] == '&' && str[i + 1] == '&')
		return (AND);
	else
		return (NILL);
}
int	create_args(t_control *control, char *args)
{
}

int	create_cmd(t_control *control, char *cmd)
{
	int		index;

	index = 0;

	while (cmd[index]) 
	{
		if(cmd[index] == '|' || cmd[index] == '&' || cmd[index] == ';')
	}	
	return (index);
}

static char	*split_token(t_control *control, char *input)
{
	char	*actual;
	int		result_cmd;
	int		result_create_cmd;
	t_cmd	*last_cmd;

	actual = input;
	while (*actual)
	{
		result_cmd = is_cmd(control, actual);
		while (!result_cmd)
		{
			result_create_cmd = create_cmd(control, actual);
			if (result_create_cmd)
			{
				last_cmd = get_last_node(control->cmd);
				last_cmd->type = result_cmd;
				create_args(control, args);
			}
		}
	}
	actual = create_cmd(control, actual);
	create_args(control, actual);
}

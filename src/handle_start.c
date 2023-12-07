#include "../include/minishell.h"
void	handle_start(t_control **header)
{
	t_control *control;

	control = *header;
	control = ft_calloc(sizeof(t_control), 1);
	control->lst = NULL;
}
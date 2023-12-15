#include "../include/minishell.h"

void	handle_start(t_control **control)
{
	*control = (t_control *)ft_calloc(sizeof(t_control), 1);
}

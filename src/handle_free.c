//
// Created by angomes- on 2/2/24.
//

#include "../include/minishell.h"

void	general_free(t_control *control)
{
	free_cmd(control);
//	free_hash_table(control->env_table);
}
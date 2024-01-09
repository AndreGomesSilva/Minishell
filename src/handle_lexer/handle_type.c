//
// Created by Alaide e Julio on 28/12/2023.
//

#include "../../include/minishell.h"

// void	set_type(t_cmd *cmd)
// {
// 	int		type;

// 	if (!cmd)
// 		return ;

// 	while (cmd)
// 	{
// 		type = 0;
// 		type = is_delimiter(cmd->cmd[0]);
// 		if (type)
// 		{
// 			if (type == 3)
// 				cmd->type = PIP;
// 			else if (type == 2)
// 			{
// 				if (is_delimiter(cmd->cmd[1]))
// 					cmd->type = HER;
// 				else
// 					cmd->type = RED;
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// }

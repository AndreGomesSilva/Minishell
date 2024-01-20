//
// Created by Alaide e Julio on 23/12/2023.
//

//#include "../../include/minishell.h"
//
//void expand_var(t_cmd *node, char **env)
//{
//	char *var;
//
//	var = &node->arg[1];
//	node->arg = get_var(var, env);
//	if (!node->arg)
//		node->arg = ft_strdup("");
//}
//
//void handle_node_var(t_cmd *cmd, char **env)
//{
//	t_arg *node;
//
//	node = cmd->list_args;
//	while(node)
//	{
//		if (is_variable(node->arg))
//			expand_var(node, env);
//		node = node->next;
//	}
//}
//
//void search_var(t_control *control, t_cmd *node)
//{
//
//}
//
//void handle_expander(t_control *control, char **env)
//{
//	t_cmd *cmd_node_temp;
//	t_cmd *cmd_node;
//
//	cmd_node = control->cmd;
//	while (cmd_node)
//	{
//		cmd_node_temp = cmd_node->next;
//		search_var(control, cmd_node);
//		cmd_node = cmd_node_temp;
//	}
//}
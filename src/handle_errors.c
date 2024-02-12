/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:29 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 17:14:38 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(t_cmd *ptr_cmd, enum e_type_error error)
{
	ptr_cmd->error_type = error;
	if (ptr_cmd->error_type == SYNTAX)
		ft_putstr_fd("Error: Syntax \n", 2);
	else if (ptr_cmd->error_type == CMD_NO_FOUND)
	{
		ft_putstr_fd(ptr_cmd->cmd, 2);
		ft_putstr_fd(": Command not found \n", 2);
	}
}

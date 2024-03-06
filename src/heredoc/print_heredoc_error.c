/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_heredoc_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:51:38 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/06 01:11:38 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_heredoc(char *eof)
{
	ft_putstr_fd("heredoc: delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n",2);
}
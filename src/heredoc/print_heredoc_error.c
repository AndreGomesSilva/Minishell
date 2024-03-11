/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_heredoc_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:51:38 by angomes-          #+#    #+#             */
/*   Updated: 2024/03/07 14:54:23 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_heredoc(char *eof)
{
	char	*new_eof;

	new_eof = remove_quotes(eof);
	ft_putstr_fd("heredoc: delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(new_eof, 2);
	ft_putstr_fd("')\n", 2);
	free(new_eof);
}

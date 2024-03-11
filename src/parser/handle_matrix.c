/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:14:51 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/11 16:02:20 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_matrix(char **matrix)
{
	char	**ptr_temp;

	ptr_temp = matrix;
	while (*matrix)
	{
		free(*matrix);
		matrix++;
	}
	free(ptr_temp);
}

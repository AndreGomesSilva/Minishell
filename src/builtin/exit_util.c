/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:25:56 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/09 18:25:59 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_big_number(char *str)
{
	int	negative;

	if (str[0] == '-')
		negative = 1;
	else
		negative = 0;
	if (ft_strlen(str) == ft_strlen(LONG_MIN)
		|| ft_strlen(str) == ft_strlen(LONG_MAX))
	{
		if (negative)
			if (ft_strncmp(str, LONG_MIN, 21) > 0)
				return (TRUE);
		if (!negative)
			if (ft_strncmp(str, LONG_MAX, 20) > 0)
				return (TRUE);
	}
	else
	{
		if (!negative && ft_strlen(str) > ft_strlen(LONG_MAX))
			return (TRUE);
		if (negative && ft_strlen(str) < ft_strlen(LONG_MIN))
			return (TRUE);
	}
	return (FALSE);
}

long	is_valid_number(char *str)
{
	int	i;

	i = -1;
	if (is_big_number(str))
		return (FALSE);
	if (!ft_atoi(str) && str[0] != '0')
		return (FALSE);
	while (i++, str[i])
	{
		if (i == 0)
		{
			if (str[i] != '-' && str[i] != '+' && !ft_isdigit(str[i]))
				return (FALSE);
		}
		else
		{
			if (!ft_isdigit(str[i]))
				return (FALSE);
		}
	}
	return (TRUE);
}

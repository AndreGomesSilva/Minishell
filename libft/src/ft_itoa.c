/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:31 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/24 21:30:27 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	count(long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*allocate(int signal, int digits)
{
	char	*str;

	if (digits == 0)
	{
		str = (char *)ft_calloc(digits + signal + 2, sizeof(char));
		if (str == NULL)
			return (NULL);
	}
	else
	{
		str = (char *)ft_calloc(digits + signal + 1, sizeof(char));
		if (str == NULL)
			return (NULL);
		if (signal == 1)
			*str = '-';
	}
	return (str);
}

static char	*zero_case(char *str, long int n_long, int index)
{
	if (n_long != 0)
		*(str + index) = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int			digits;
	char		*str;
	int			index;
	long int	n_long;
	int			sign;

	index = -1;
	n_long = n;
	sign = 0;
	digits = count(n_long);
	if (n_long < 0)
	{
		sign = 1;
		n_long *= -1;
	}
	str = allocate(sign, digits);
	if (str == NULL)
		return (NULL);
	while (index++, index <= digits - 1)
	{
		*(str + digits + sign - index - 1) = n_long % 10 + 48;
		n_long = n_long / 10;
	}
	zero_case(str, n_long, index);
	return (str);
}

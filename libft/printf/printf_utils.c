/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:47:31 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/30 15:31:19 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	convert_to_hexa(char *result, unsigned long number)
{
	int				number_c;
	unsigned long	remainder;
	char			hex_number;
	char			temp[20];
	int				start;

	number_c = -1;
	start = -1;
	if (utils(result, 'x', number))
		return (1);
	while (number_c++, number != 0)
	{
		remainder = number % 16;
		if (remainder < 10)
			hex_number = remainder + '0';
		else
			hex_number = 'a' + remainder - 10;
		*(temp + number_c) = hex_number;
		number /= 16;
	}
	*(temp + number_c) = '\0';
	while (++start, number_c)
		*(result + start) = *(temp + number_c-- - 1);
	*(result + start) = '\0';
	return (start);
}

int	utils(char *str, char type, unsigned long number)
{
	if (type == 's')
	{
		if (!str)
			return (write(1, "(null)", 6));
	}
	else if (type == 'p')
	{
		if (!*str)
			return (write(1, "(nil)", 5));
	}
	else if (type == 'x' && number == 0)
	{
		*str = '0';
		*(str + 1) = '\0';
		return (1);
	}
	return (0);
}

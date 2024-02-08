/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:45:08 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/24 21:18:40 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	print_cs(char **str, va_list args)
{
	int		number_c;
	int		param;
	char	*param_str;

	if (**str == 'c')
	{
		param = va_arg(args, int);
		write(1, &param, 1);
		number_c = 1;
	}
	else
	{
		number_c = -1;
		param_str = va_arg(args, char *);
		if (utils(param_str, 's', 0))
			return (6);
		while (++number_c, *param_str)
		{
			write(1, param_str, 1);
			param_str++;
		}
	}
	return (number_c);
}

static int	print_diu(char **str, va_list args, char space)
{
	char	*param_str;
	int		number_c;
	int		n;

	number_c = -1;
	if (**str == 'u')
		param_str = ft_itoa(va_arg(args, unsigned int));
	else
	{
		n = (int)va_arg(args, int);
		param_str = ft_itoa(n);
		if (n >= 0 && space == 's')
			write(1, " ", 1);
	}
	while (++number_c, *(param_str + number_c))
		write(1, &*(param_str + number_c), 1);
	free(param_str);
	if (**str != 'u' && n >= 0 && space == 's')
		number_c++;
	return (number_c);
}

static int	print_xp(char **str, unsigned long unlo)
{
	unsigned long	number;
	char			param_s[20];
	int				index;
	char			str_res;

	index = -1;
	if (*(*str) == 'p')
		number = convert_to_hexa(param_s, unlo);
	else
		number = convert_to_hexa(param_s, (unsigned int)unlo);
	while (index++, number--)
	{
		if (index == 0 && *(*str) == 'p')
			write(1, "0x", 2);
		if (*(*str) == 'x')
			str_res = ft_tolower(*(param_s + index));
		else if (*(*str) == 'X')
			str_res = ft_toupper(*(param_s + index));
		else
			str_res = *(param_s + index);
		write(1, &str_res, 1);
	}
	if (*(*str) == 'p')
		index += 2;
	return (index);
}

static int	print_control(char **str, va_list args, char space)
{
	int				number_n;
	unsigned long	ulo;

	if (**str == 'c' || **str == 's')
		number_n = print_cs(str, args);
	else if (**str == 'x' || **str == 'X' || **str == 'p')
	{
		ulo = va_arg(args, unsigned long);
		if (**str == 'p' && ulo == 0)
		{
			(*str)++;
			return (utils("", 'p', 0));
		}
		number_n = print_xp(str, ulo);
	}
	else if (**str == 'd' || **str == 'i' || **str == 'u')
		number_n = print_diu(str, args, space);
	else
	{
		if (**str == '%')
			write(1, "%", 1);
		number_n = 1;
	}
	(*str)++;
	return (number_n);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		number_printed;

	number_printed = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str != '%' && ++number_printed && str++)
			write(1, (str - 1), 1);
		else
		{
			if (++str && *str == ' ')
			{
				while (*str && *str == ' ')
					str++;
				number_printed += print_control((char **)&str, args, 's');
			}
			else
				number_printed += print_control((char **)&str, args, 'n');
		}
	}
	va_end(args);
	return (number_printed);
}

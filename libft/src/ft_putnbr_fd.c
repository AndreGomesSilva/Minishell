/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:31 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/24 21:30:44 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	n_l;

	n_l = n;
	if (n_l < 0)
	{
		ft_putchar_fd('-', fd);
		n_l = n_l * -1;
	}
	if (n_l >= 10)
		ft_putnbr_fd(n_l / 10, fd);
	ft_putchar_fd((n_l % 10) + '0', fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:31 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/24 21:28:36 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	len_sub;
	int		result;

	result = 0;
	index = 0;
	len_sub = ft_strlen(little);
	if (len_sub == 0)
		return ((char *)big);
	while (*big && len >= len_sub)
	{
		result = ft_strncmp(big, little, len_sub);
		if (result == 0)
			return ((char *)big + index);
		big++;
		len--;
	}
	return (NULL);
}

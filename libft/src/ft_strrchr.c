/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:31 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/24 21:28:31 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_last;
	char	character;
	int		finded;

	finded = 0;
	character = (unsigned char)c;
	s_last = (char *)s;
	while (*(s))
	{
		if (*(s) == character)
		{
			s_last = (char *)s;
			finded = 1;
		}
		s++;
	}
	if (*(s) == character)
		return ((char *)s);
	if (finded == 1)
	{
		return (s_last);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:31 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/24 21:29:46 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	count_keywords(char *s, char c)
{
	int	sun_keywords;

	sun_keywords = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			sun_keywords++;
			while (*s && *s != c)
				s++;
		}
	}
	return (sun_keywords);
}

char	**ft_split(char const *s, char c)
{
	char	**s_final;
	int		len_keywords;
	int		len;
	int		index;

	index = -1;
	if (s == NULL)
		return (NULL);
	len_keywords = count_keywords((char *)s, c);
	s_final = (char **)ft_calloc(len_keywords + 1, sizeof(char *));
	if (s_final == NULL)
		return (NULL);
	while (index++, index < len_keywords)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (*(s + len) && *(s + len) != c)
			len++;
		*(s_final + index) = ft_substr(s, 0, len);
		if (*(s_final + index) == NULL)
			return (NULL);
		s += len;
	}
	return (s_final);
}

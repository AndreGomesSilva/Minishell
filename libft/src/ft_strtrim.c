/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:35:31 by r-afonso          #+#    #+#             */
/*   Updated: 2023/10/24 21:28:27 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*go_malloc(size_t size, int type)
{
	char	*str;

	str = (char *)ft_calloc(size, type);
	if (str == NULL)
		return (NULL);
	if (size == 1)
		*str = '\0';
	return (str);
}

void	generate_result(char *dst, char *entry, int start, int stop)
{
	int	index;

	index = 0;
	while (start <= stop)
	{
		*(dst + index) = *(entry + start);
		start++;
		index++;
	}
	*(dst + index) = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		stop;

	if (set == NULL || s1 == NULL)
		return ((char *)s1);
	start = 0;
	while (ft_strchr(set, s1[start]) != NULL && s1[start] != '\0')
		start++;
	stop = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[stop]) != NULL && stop > start)
		stop--;
	if (stop < start)
		str = go_malloc(1, sizeof(char));
	else
	{
		str = go_malloc(stop - start + 2, sizeof(char));
		if (str == NULL)
			return (NULL);
		generate_result(str, (char *)s1, start, stop);
	}
	return (str);
}

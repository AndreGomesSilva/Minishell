/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:31:53 by angomes-          #+#    #+#             */
/*   Updated: 2024/02/11 00:02:52 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	str_compare(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	result;

	result = 0;
	len1 = strlen(s1);
	len2 = strlen(s2);
	if (len2 > len1)
		result = ft_strncmp(s1, s2, len2);
	else
		result = ft_strncmp(s1, s2, len1);
	return (result);
}

char	*swap_string(char *str, char *sub_str)
{
	char	*result;

	result = NULL;
	if (str && sub_str)
	{
		result = ft_strjoin(str, sub_str);
		free(str);
		free(sub_str);
	}
	else if (sub_str)
		result = sub_str;
	else if (str)
		result = str;
	return (result);
}

char	*remove_quotes(char *str)
{
	int		i;
	char	type_quote;
	char	*ptr_str;
	char	*result;

	ptr_str = str;
	result = NULL;
	while (str && *str)
	{
		if (*str == '"' || *str == '\'')
		{
			type_quote = *str++;
			i = 0;
			while (str[i] && str[i] != type_quote)
				i++;
			result = swap_string(result, ft_substr(str, 0, i));
			str = &str[i];
		}
		else if (*str)
			str++;
	}
	if (!result)
		result = ft_strdup(ptr_str);
	return (result);
}

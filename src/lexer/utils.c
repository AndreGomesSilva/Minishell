/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angomes- <angomes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:17:54 by r-afonso          #+#    #+#             */
/*   Updated: 2024/03/05 20:35:00 by angomes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	if (c != 0 && (c == ' ' || c == '\t'))
		return (TRUE);
	return (FALSE);
}

int	str_compare(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	result;

	result = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len2 > len1)
		result = ft_strncmp(s1, s2, len2);
	else
		result = ft_strncmp(s1, s2, len1);
	return (result);
}

enum e_type_arg	is_arg(char *actual)
{
	if (!actual || !*actual)
		return (NORM);
	if (*actual == '<')
	{
		if (*(actual + 1) == '<')
			return (REDIRECT_HERD);
		else
			return (REDIRECT_INPUT);
	}
	else if (*actual == '>')
	{
		if (*(actual + 1) == '>')
			return (REDIRECT_OUTPUT_APPEND);
		else
			return (REDIRECT_OUTPUT);
	}
	return (set_type(actual));
}

int	len_string_token(char *str)
{
	int		n_quote;
	char	type_of_quote;
	int		i;

	i = -1;
	n_quote = 0;
	while (i++, str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			type_of_quote = str[i];
			n_quote++;
			while (str[++i] && n_quote % 2 != 0)
			{
				if (str[i] == type_of_quote && n_quote++)
					break;
			}
		}
		if (!str[i] || str[i] == ' ' || str[i] == '|'
			|| is_arg(&str[i]) > BROKEN_QUOTES)
			break ;
	}
	return (i);
}

int	get_token_len(char *str, int type)
{
	int	len;

	len = 0;
	if (type == REDIRECT_INPUT || type == REDIRECT_OUTPUT)
		len += 1;
	else if (type == REDIRECT_OUTPUT_APPEND || type == REDIRECT_HERD)
		len += 2;
	else if (str[len] && ((is_arg(&str[len]) <= BROKEN_QUOTES)))
		len = len_string_token(str);
	return (len);
}

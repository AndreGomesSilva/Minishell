/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:15:51 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/12 23:38:57 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	partition(char *arr[], int start, int end)
{
	char	*pivot;
	int		i;
	int		j;
	char	*temp;

	i = start - 1;
	pivot = arr[end];
	j = start;
	while (j < end)
	{
		j++;
		if (ft_strncmp(arr[j], pivot, ft_strlen(arr[j])) < 0)
		{
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	temp = arr[i + 1];
	arr[i + 1] = arr[end];
	arr[end] = temp;
	return (i + 1);
}

void	sort_matrix(char *arr[], int start, int end)
{
	int	pivot;

	if (start < end)
	{
		pivot = partition(arr, start, end);
		sort_matrix(arr, start, pivot - 1);
		sort_matrix(arr, pivot + 1, end);
	}
}

int	ft_pow(int base, int exponent)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	if (exponent == 0)
		return (result);
	while (i < exponent)
	{
		result *= base;
		i++;
	}
	return (result);
}

int	get_size_matrix(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	get_size_env_key(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

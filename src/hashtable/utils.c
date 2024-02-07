#include "../../include/minishell.h"

int partition(char *arr[], int start, int end) {
	char *pivot;
	int i;
	int j;

	i = start - 1;
	pivot = arr[end];
	j = start;
	while(j < end && j++)
		if (ft_strncmp(arr[j], pivot, ft_strlen(arr[j])) < 0)
		{
			i++;
			char *temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	char *temp = arr[i + 1];
	arr[i + 1] = arr[end];
	arr[end] = temp;
	return i + 1;
}

void matrix_quicksort(char *arr[], int start, int end) {
	if (start < end) {
		int pivot;
		pivot = partition(arr, start, end);

		matrix_quicksort(arr, start, pivot - 1);
		matrix_quicksort(arr, pivot + 1, end);
	}
}

int	ft_pow(int base, int exponent)
{
	int result;
	int i;

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

int	len_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int strlen_var_name(const char *str)
{
	int i;
	i = 0;

	while(str[i] && str[i] != '=')
		i++;
	return (i);
}

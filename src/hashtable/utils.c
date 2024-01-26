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

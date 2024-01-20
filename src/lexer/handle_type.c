
#include "../../include/minishell.h" 

int handle_quotes(char *str, int *iterator, int *n_quotes, int *flag_var)
{
	char type_of_quote;

	type_of_quote = str[*iterator];
	*iterator = *iterator + 1;
	*n_quotes = *n_quotes + 1;
	while (str[*iterator] && *n_quotes % 2 != 0)
	{
		if (type_of_quote == '"')
			*flag_var += is_variable(&str[*iterator]);
		if (str[*iterator] == type_of_quote)
		{
			*n_quotes = *n_quotes + 1;
			break;
		}
		*iterator = *iterator + 1;
	}
	if (*n_quotes % 2 != 0)
		return (BROKEN_QUOTES);
	*n_quotes = 0;
	return (0);
}

enum e_type_arg set_type(char *str)
{
    int n_quotes;
    int flag_var;
    int i;

    i = -1;
    n_quotes = 0;
	flag_var = 0;
    while (i++, str[i])
    {

        if (str[i] == '"' || str[i] == '\'')
        {
			if (handle_quotes(str, &i, &n_quotes, &flag_var))
				return (BROKEN_QUOTES);
        }
        if (str[i] && !n_quotes)
            flag_var += is_variable(&str[i]);
    }
    if (flag_var)
        return (VAR_EXPAND);
    return (NORM);
}

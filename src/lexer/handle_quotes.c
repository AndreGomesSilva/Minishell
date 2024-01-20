
#include "../../include/minishell.h" 

enum e_type_arg set_type_args(char *str)
{
    int n_quotes;
    char type_of_quote;
    int flag_var;
    int i;

    i = -1;
    n_quotes = 0;
	flag_var = 0;
    while (i++, str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            type_of_quote = str[i];
            i++;
            n_quotes++;
            while (str[i] && n_quotes % 2 != 0)
            {
                if (type_of_quote == '"')
                    flag_var += is_variable(&str[i]);
                if (str[i] == type_of_quote)
                {
                    n_quotes++;
                    break;
                }
                i++;
            }
            if (n_quotes % 2 != 0)
                return (BROKEN_QUOTES);
            n_quotes = 0;
        }
        if (str[i] && !n_quotes)
            flag_var += is_variable(&str[i]);
    }
    if (flag_var)
        return (VAR_EXPAND);
    return (NORM);
}

int	handle_quotes(char *str)
{
	int n_quote;
	int type_of_quote;
	int i;

	i = 0;
	n_quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			type_of_quote = str[i];
			n_quote++;
			i++;
			while (str[i] && n_quote % 2 != 0)
			{
				if (str[i] == type_of_quote)
					n_quote++;
				i++;
			}
		}
		if (!str[i] || str[i] == ' ' || str[i] == '|' || is_arg(&str[i]) > BROKEN_QUOTES )
			break;
		i++;
	}
	return (i);
}
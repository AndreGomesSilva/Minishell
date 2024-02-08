/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:59:35 by r-afonso          #+#    #+#             */
/*   Updated: 2024/02/08 14:33:52 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: corrigir entrada por matriz e testar
// int	handle_cd(char **matriz)
// {
// 	const char	*pwd_target = matriz[1];
// 	char	*pwd_relative;
// 	char	*pwd;

// 	if (matriz[2] != NULL) {
//         fprintf(stderr, "cd: too many arguments\n");
//         return 0;
//     }

// 	if (chdir(pwd_target) != 0)
// 	{
// 		pwd = getcwd(NULL, NULL);
// 		pwd_relative = ft_strjoin((const char *)pwd, (const char *)pwd_target);
// 		free(pwd);
// 		if (chdir(pwd_relative) != 0)
// 		{
// 			free(pwd_relative);
// 			return (FALSE);
// 		}
// 		else
// 		{
// 			free(pwd_relative);
// 			return (TRUE);
// 		}
// 	}
// 	return (TRUE);
// }

int handle_cd_continuation(char *pwd_target) {
    char *pwd_relative;
    char *pwd;

    if (chdir(pwd_target) != 0) {
        pwd = getcwd(NULL, 0);
        pwd_relative = ft_strjoin(pwd, pwd_target);
        free(pwd);
        if (chdir(pwd_relative) != 0) {
            free(pwd_relative);
            return 0;
        } else {
            free(pwd_relative);
            return 1;
        }
    }
    return 1;
}

int handle_cd(char **matriz) {
    if (matriz[2] != NULL) {
        char *error_message = "cd: too many arguments\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
        return 0;
    }
   	return handle_cd_continuation(matriz[1]);
}

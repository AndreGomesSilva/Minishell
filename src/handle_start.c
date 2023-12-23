#include "../include/minishell.h"

void	set_path(t_control *control, char **env)
{
	char *temp_pwd;
	char *temp_user;

	temp_user = NULL;
	control->pwd = get_var("PWD", env);
	control->user = get_var("USER", env);
	if (!control->user)
		control->user = get_var("GUEST", env);
	temp_user = ft_strjoin(control->user, "@Minishell:");
	temp_pwd = ft_strjoin(temp_user ,control->pwd);
	control->prompt = ft_strjoin(temp_pwd, "$ ");
	free(temp_user);
	free(temp_pwd);
}

void	handle_start(t_control **control, char **env)
{
	*control = (t_control *)ft_calloc(sizeof(t_control), 1);
	set_path(*control, env);
}

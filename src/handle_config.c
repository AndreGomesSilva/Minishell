#include "../include/minishell.h"

void	set_path(t_control *control)
{
	char	*pwd;
	char	*user;
	char	*temp_pwd;
	char	*temp_user;

	pwd = get_var(control, "PWD");
	user = get_var(control, "USER");
	if (pwd)
			control->pwd_initial = handle_home_path(control, pwd);
	if (user)
		control->user = user;
	else
	 	control->user = ft_strdup("GUEST");
	temp_user = ft_strjoin(control->user, "@Minishell:");
	temp_pwd = ft_strjoin(temp_user, control->pwd_initial);
	control->prompt = ft_strjoin(temp_pwd, "$ ");
	free(temp_user);
	free(temp_pwd);
}

int handle_envp(t_control *control, char **env)
{
	t_table *table;
	
	table = init_table(control, env);
	control->env = env;
	copy_env(control, env);
	print_hash_table(table);
	printf("\n FINISH \n");
	return (TRUE);
}

void	handle_config(t_control **control, char **env)
{
	*control = (t_control *)ft_calloc(sizeof(t_control), 1);
	handle_envp(*control, env);
	set_path(*control);
}

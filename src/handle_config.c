#include "../include/minishell.h"

void	set_path(t_control *control, char **env)
{
	char	*temp_pwd;
	char	*temp_user;

	temp_user = NULL;
	temp_pwd = NULL;
	control->env = env;
	control->pwd_initial = strdup(getenv("PWD"));
	control->user = strdup(getenv("USER"));
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
	copy_env(control, env);
	print_hash_table(table);
	printf("\n FINISH \n");
	return (TRUE);
}

void	handle_config(t_control **control, char **env)
{
	*control = (t_control *)ft_calloc(sizeof(t_control), 1);
	set_path(*control, env);
	handle_envp(*control, env);
}

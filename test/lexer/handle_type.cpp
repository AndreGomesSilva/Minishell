#include "../../include/minishell.h"
#include <gtest/gtest.h>

t_control *start_config(void) {
    t_control *g_control;
    char **env;
    env = environ;
    handle_config(&g_control, env);
    return (g_control);
}
TEST(handle_type, handle_quotes) {
    // t_control *g_control = start_config();
    // char actual[] = "echo hello world";

    // handle_quotes(char *str, int *iterator, int *n_quotes, int *flag_var)

    // char *expected = ft_strjoin(g_control->cmd->cmd, " ");
    // expected = ft_strjoin(expected, g_control->cmd->list_args->arg);
    // expected = ft_strjoin(expected, " ");
    // expected = ft_strjoin(expected, g_control->cmd->list_args->next->arg);
    // EXPECT_STREQ(actual, expected);
}

#include "../../include/minishell.h"
#include <gtest/gtest.h>

extern "C" {
char *readline(const char *prompt);
}

// Funções "mock" que simulam readline e add_history
// char* mock_readline(const char* prompt) {
//     // Implemente o retorno de um comando simulado
//     return strdup("echo teste |");
// }

// extern char **environ;
// Caso de teste para a função handle_input
// TEST(HandleInputTest, HandleValidInput) {
//     t_control *g_control;
// 	char	**env;
// 	env = environ;

// 	handle_config(&g_control, env);

//     readline = mock_readline;

//     // Chame a função handle_input e verifique o resultado
//     handle_token(g_control);
//     ASSERT_EQ(result, TRUE);
// Substitua TRUE pelo valor correspondente

//     Adicione verificações adicionais conforme necessário

// handle_token(g_control, (char *)"echo hello world");
// }
t_control *start_config(void) {
    t_control *g_control;
    char **env;
    env = environ;
    handle_config(&g_control, env);
    return (g_control);
}
TEST(handle_token, handle_token) {
    t_control *g_control = start_config();
    char actual[] = "echo hello world";

    handle_token(g_control, actual);

    char *expected = ft_strjoin(g_control->cmd->cmd, " ");
    expected = ft_strjoin(expected, g_control->cmd->list_args->arg);
    expected = ft_strjoin(expected, " ");
    expected = ft_strjoin(expected, g_control->cmd->list_args->next->arg);
    EXPECT_STREQ(actual, expected);
}

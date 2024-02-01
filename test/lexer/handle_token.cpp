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
TEST(handle_token, create_arg) {
    t_control *g_control;
    char *actual;
    actual = ft_strdup("echo hello world");

    g_control = start_config();
    for (int count = 0; count < 10; count++) {
        actual = create_cmd(g_control, actual);
    }
    EXPECT_TRUE(true);
}
// #include "../../include/minishell.h"
// #include <gtest/gtest.h>

// extern "C" {
//     // Declaração de funções externas que você irá "mockar"
//     char* readline(const char* prompt);
//     void add_history(const char* line);
// }

// // Funções "mock" que simulam readline e add_history
// char* mock_readline(const char* prompt) {
//     // Implemente o retorno de um comando simulado
//     return strdup("echo teste |");
// }

// void mock_add_history(const char* line) {
//     // Implemente a lógica de adição no histórico se necessário
// }

// extern char **environ;
// // Caso de teste para a função handle_input
// TEST(HandleInputTest, HandleValidInput) {
//     t_control *g_control;
// 	char	**env;
// 	env = environ;
	
// 	handle_start(&g_control, env);

//     readline = mock_readline;
//     add_history = mock_add_history;

//     // Chame a função handle_input e verifique o resultado
//     int result = handle_input(g_control);
//     ASSERT_EQ(result, TRUE); // Substitua TRUE pelo valor correspondente

    // Adicione verificações adicionais conforme necessário
// }
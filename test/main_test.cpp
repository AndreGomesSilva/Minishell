#include "../include/minishell.h"

#include <gtest/gtest.h>

t_control	*g_control;
int	main(int argc, char **argv)
{
	g_control = NULL;
	testing::InitGoogleTest(&argc, argv);
	return (RUN_ALL_TESTS());
}
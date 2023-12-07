#include "../include/minishell.h"
#include <gtest/gtest.h>

TEST(AddTest, HandlesOne)
{
	EXPECT_EQ(func_test(), 0);
}

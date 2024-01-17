#include <gtest/gtest.h>

#include "../../include/minishell.h"

TEST(utils, is_space) {
    char c = ' ';
	int result;
	
	result = is_space(c);
    ASSERT_EQ(result, TRUE);
}

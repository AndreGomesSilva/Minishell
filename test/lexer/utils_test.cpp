#include "../../include/minishell.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <vector>

TEST(lexer_utils, is_space_valid) {
    EXPECT_TRUE(is_space(' '));
}

TEST(lexer_utils, is_space_invalid) {
    EXPECT_FALSE(is_space('a'));
    EXPECT_FALSE(is_space('1'));
    EXPECT_FALSE(is_space('\n'));
}

TEST(lexer_utils, is_arg_valid) {
	std::vector<int> options = {0, 1, 2, 3, 4, 5, 6};
	char str[] = ">";
	int result = is_arg(str);
	EXPECT_THAT(options, testing::Contains(result));
	
	char str_2[] = ">>";
	result = is_arg(str_2);
	EXPECT_THAT(options, testing::Contains(result));
	
	char str_3[] = "<";
	result = is_arg(str_3);
	EXPECT_THAT(options, testing::Contains(result));
	
	char str_4[] = "<<";
	result = is_arg(str_4);
	EXPECT_THAT(options, testing::Contains(result));
}

TEST(lexer_utils, is_arg_invalid) {
    std::vector<int> options = {1, 2, 3, 4, 5, 6};
	char str[] = "c";
    int result = is_arg(str);
    auto it = std::find(options.begin(), options.end(), result);
    EXPECT_TRUE(it == options.end());
}

TEST(lexer_utils, is_cmd){
	
}

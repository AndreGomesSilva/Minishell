#include "../include/minishell.h"

#include <gtest/gtest.h>

TEST(AddTest, HandlesOne) {
 EXPECT_EQ(func_test(), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

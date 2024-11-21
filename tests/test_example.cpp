#include <cmath>
#include <gtest/gtest.h>
#include "../src/test_class.hpp"

TEST(sqrt, integer) { EXPECT_EQ(2, std::sqrt(4)); }

TEST(test_class, correct_return_value) { EXPECT_EQ(2, foo()); }

// This test should fail
TEST(test_class, incorrect_return_value) { EXPECT_EQ(3, foo()); }
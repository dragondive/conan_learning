#include "gtest/gtest.h"
#include "sample.h"

TEST(SampleTest, get_42)
{
    EXPECT_EQ(42, get_42());
}

TEST(SampleTest, get_hello)
{
    EXPECT_EQ("hello", get_hello());
}

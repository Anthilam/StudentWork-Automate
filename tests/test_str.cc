#include "str.h"

#include "gtest/gtest.h"

TEST(StringTest, Length) {
  EXPECT_TRUE(str_length(NULL) == 0);
  EXPECT_TRUE(str_length("") == 0);
  EXPECT_TRUE(str_length("a") == 1);
  EXPECT_TRUE(str_length("azertyuiopqsdfghjklmwxcvbn ") == 27);
}

TEST(StringTest, Compare) {
  EXPECT_TRUE(str_compare("a", "b") < 0);
  EXPECT_TRUE(str_compare("b", "a") > 0);
  EXPECT_TRUE(str_compare("a", "a") == 0);
  EXPECT_TRUE(str_compare("abcdef", "abcdeg") < 0);
}

TEST(StringTest, Search) {
  const char *h1 = "azertyuio";

  EXPECT_TRUE(str_search(h1, "az") == h1);
  EXPECT_TRUE(str_search(h1, "t") == h1 + 4);
  EXPECT_TRUE(str_search(h1, "tyuio") == h1 + 4);
  EXPECT_TRUE(str_search(h1, "tyuiop") == NULL);

  const char *h2 = "aaaaaaaaaaaaaaaaab";

  EXPECT_TRUE(str_search(h2, "aaaaab") == h2 + 12);
}

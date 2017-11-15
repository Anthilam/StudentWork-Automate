#include "fa.h"

#include "gtest/gtest.h"

// Test de reference
TEST(nomDuSource,nomDeLaFonction){
  EXPECT_TRUE(0 ==0);
}

TEST(fa,fa_create){
  struct fa a1;
  fa_create(&a1,2,3);
  EXPECT_TRUE(a1.alpha_count == 2);
  fa_destroy(&a1);
}

TEST(fa,fa_destroy){
  struct fa a1;
  fa_create(&a1,2,3);
  EXPECT_TRUE(a1.alpha_count == 2);
  fa_destroy(&a1);
}

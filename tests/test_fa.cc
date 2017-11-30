#include "fa.h"

#include "gtest/gtest.h"

// Test de reference
TEST(nomDuSource,nomDeLaFonction){
  EXPECT_TRUE(0 ==0);
}
/* Minimum pour chaque test
struct fa a1;
fa_create(&a1,2,3);

fa_destroy(&a1);
*/

TEST(fa,createEmpty){
  struct fa a1;
  fa_create(&a1,2,3);
  EXPECT_TRUE(a1.alpha_count == 2);
  EXPECT_TRUE(a1.state_count == 3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  for(int i=0;i<3;i++){
    for(int j=0;j<2;j++){
        EXPECT_TRUE(a1.state_array[i][j].first == NULL);
    }
  }
  /* size and used not initialize */
  EXPECT_TRUE(a1.array_init.value==NULL);
  EXPECT_TRUE(a1.array_init.used==0);
  EXPECT_TRUE(a1.array_init.size==0);
  EXPECT_TRUE(a1.array_final.value==NULL);
  EXPECT_TRUE(a1.array_final.used==0);
  EXPECT_TRUE(a1.array_final.size==0);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_destroy(&a1);
}

TEST(fa,setInitiale){
  struct fa a1;
  fa_create(&a1,3,4);
  fa_set_state_initial(&a1,1);
  EXPECT_TRUE(a1.array_init.value[0]== 1);
  EXPECT_TRUE(a1.array_init.used == 1);
  fa_set_state_initial(&a1,0);
  EXPECT_TRUE(a1.array_init.value[0]== 1);
  EXPECT_TRUE(a1.array_init.value[1]== 0);
  EXPECT_TRUE(a1.array_init.used == 2);
  fa_set_state_initial(&a1,0);
  EXPECT_TRUE(a1.array_init.used == 2);
  fa_set_state_initial(&a1,6);
  EXPECT_TRUE(a1.array_init.used == 2);
  fa_set_state_initial(&a1,-6);
  EXPECT_TRUE(a1.array_init.used == 2);
  fa_destroy(&a1);
}

TEST(fa,setFinal){
  struct fa a1;
  fa_create(&a1,3,4);
  fa_set_state_final(&a1,1);
  EXPECT_TRUE(a1.array_final.value[0]== 1);
  EXPECT_TRUE(a1.array_final.used == 1);
  fa_set_state_final(&a1,0);
  EXPECT_TRUE(a1.array_final.value[0]== 1);
  EXPECT_TRUE(a1.array_final.value[1]== 0);
  EXPECT_TRUE(a1.array_final.used == 2);
  fa_set_state_final(&a1,0);
  EXPECT_TRUE(a1.array_final.used == 2);
  fa_set_state_final(&a1,6);
  EXPECT_TRUE(a1.array_final.used == 2);
  fa_set_state_final(&a1,-6);
  EXPECT_TRUE(a1.array_final.used == 2);
  fa_destroy(&a1);
}

TEST(fa,addOneTransition){
  struct fa a1;
  fa_create(&a1,3,4);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_add_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_destroy(&a1);
}

TEST(fa,addAllTransition){
  struct fa a1;
  fa_create(&a1,3,4);
  fa_add_transition(&a1,0,'a',-3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,0,'g',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,-1,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_add_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
    EXPECT_TRUE(fa_count_transitions(&a1)== (nbAlph+1)*4*4 );
  }
  fa_destroy(&a1);
}

TEST(fa,removeOneTransition){
  struct fa a1;
  fa_create(&a1,3,4);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,0,'a',1);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_add_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==2);
  fa_remove_transition(&a1,0,'a',2);
  EXPECT_TRUE(fa_count_transitions(&a1)==2);
  fa_remove_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_remove_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_destroy(&a1);
}

TEST(fa,removeAllTransition){
  struct fa a1;
  fa_create(&a1,3,4);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_add_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
    EXPECT_TRUE(fa_count_transitions(&a1)== (nbAlph+1)*4*4 );
  }
  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_remove_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
    EXPECT_TRUE(fa_count_transitions(&a1)== 48-((nbAlph+1)*4*4) );
  }
  fa_remove_transition(&a1,0,'a',-3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_remove_transition(&a1,0,'g',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_remove_transition(&a1,-1,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_destroy(&a1);
}

TEST(fa,removeState){
  struct fa a1;
  fa_create(&a1,2,3);
  EXPECT_TRUE(a1.state_count == 3);
  fa_remove_state(&a1,-3);
  EXPECT_TRUE(a1.state_count == 3);
  fa_remove_state(&a1,2);
  fa_remove_state(&a1,2);
  EXPECT_TRUE(a1.state_count == 2);
  fa_remove_state(&a1,1);
  EXPECT_TRUE(a1.state_count == 1);
  fa_remove_state(&a1,0);
  EXPECT_TRUE(a1.state_count == 0);
  fa_destroy(&a1);
}

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

TEST(fa,createWrong){
  struct fa a1,a2,a3,a4;
  // Verification de la validite des arguments
  fa_create(&a1,2,-3);
  fa_create(&a2,-2,3);
  fa_create(&a3,0,3);
  fa_create(&a4,2,0);
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

  // peut on ajouter un etat non existant ?
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
  // peut on ajouter un etat non existant ?
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
  // Ajouts d'une transistion existante
  fa_add_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_destroy(&a1);
}

TEST(fa,addAllTransition){
  struct fa a1;
  fa_create(&a1,3,4);
  // ajout de transitions incorrectes
  fa_add_transition(&a1,0,'a',-3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,0,'g',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,-1,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  // ajouts exaustif des toutes les transitions avec toutes les lettres
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
  // ajout de transitions
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,0,'a',1);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_add_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==2);


  // suppression d'une transistion non existante
  fa_remove_transition(&a1,0,'a',2);
  EXPECT_TRUE(fa_count_transitions(&a1)==2);
  // suppression d'une transition
  fa_remove_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  // suppression d'une transition venant d'etre supprime
  fa_remove_transition(&a1,0,'a',3);
  EXPECT_TRUE(fa_count_transitions(&a1)==1);
  fa_destroy(&a1);
}

TEST(fa,removeAllTransition){
  struct fa a1;
  fa_create(&a1,3,4);
  // on ajoutes toutes les transistions
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_add_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
    EXPECT_TRUE(fa_count_transitions(&a1)== (nbAlph+1)*4*4 );
  }
  // on les supprimes toutes
  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_remove_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
    EXPECT_TRUE(fa_count_transitions(&a1)== 48-((nbAlph+1)*4*4) );
  }
  // on essaye de supprimes des transisitions incorrectes
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
  // Suppressions d'états non valide
  fa_remove_state(&a1,-3);
  EXPECT_TRUE(a1.state_count == 3);
  fa_remove_state(&a1,10);
  EXPECT_TRUE(a1.state_count == 3);
  // Suppressions de tous les états 1 par 1
  fa_remove_state(&a1,2);
  EXPECT_TRUE(a1.state_count == 2);
  fa_remove_state(&a1,2);
  EXPECT_TRUE(a1.state_count == 2);
  fa_remove_state(&a1,1);
  EXPECT_TRUE(a1.state_count == 1);
  fa_remove_state(&a1,0);
  EXPECT_TRUE(a1.state_count == 0);
  fa_destroy(&a1);
}

TEST(fa,isDeterminist){
  struct fa a1;
  fa_create(&a1,2,3);
  EXPECT_TRUE(!fa_is_deterministic(&a1));
  // ajout d'un etat initial
  fa_set_state_initial(&a1,0);
  EXPECT_TRUE(fa_is_deterministic(&a1));

  // ajout d'un etat final
  fa_set_state_final(&a1,1);
  EXPECT_TRUE(fa_is_deterministic(&a1));
  // ajouts de plusieurs etats finaux
  fa_set_state_final(&a1,0);
  fa_set_state_final(&a1,2);
  EXPECT_TRUE(fa_is_deterministic(&a1));
  // ajout de transitions
  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,0,'b',2);
  fa_add_transition(&a1,1,'a',1);
  fa_add_transition(&a1,1,'b',2);
  EXPECT_TRUE(fa_is_deterministic(&a1));
  // ajout de plusieurs transisitons le rendant non deter.
  fa_add_transition(&a1,0,'a',3);
  fa_add_transition(&a1,0,'b',1);
  fa_add_transition(&a1,1,'a',3);
  fa_add_transition(&a1,1,'b',1);
  fa_destroy(&a1);
}

#include "fa.h"

#include "gtest/gtest.h"

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
TEST(fa,setLotInitiale){
  struct fa a1;
  fa_create(&a1,3,40);
  for(size_t nbState=0;nbState<40;nbState++){
      fa_set_state_initial(&a1,nbState);
      EXPECT_TRUE(a1.array_init.used == nbState+1);
  }
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

TEST(fa,setLotFinal){
  struct fa a1;
  fa_create(&a1,3,40);
  for(size_t nbState=0;nbState<40;nbState++){
      fa_set_state_final(&a1,nbState);
      EXPECT_TRUE(a1.array_final.used == nbState+1);
  }
  fa_destroy(&a1);
}

TEST(fa,addSomeTransition){
  struct fa a1;
  fa_create(&a1,3,4);
  EXPECT_TRUE(fa_count_transitions(&a1)==0);
  fa_add_transition(&a1,0,'a',-1);
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

TEST(fa,faPrint){
  struct fa a1;
  fa_create(&a1, 2, 2);

  fa_add_transition(&a1, 0, 'a', 1);
  fa_add_transition(&a1, 0, 'a', 0);
  fa_add_transition(&a1, 1, 'a', 1);
  fa_add_transition(&a1, 1, 'b', 1);

  fa_set_state_initial(&a1, 0);
  fa_set_state_final(&a1, 1);

  fa_pretty_print(&a1,stdout);
  fa_dot_print(&a1,stdout);

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
  fa_add_transition(&a1,0,'a',2);
  EXPECT_TRUE(fa_count_transitions(&a1)==3);
  // suppression d'une transistion situe entre deux
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
  fa_set_state_final(&a1,2);
  fa_set_state_final(&a1,1);
  fa_set_state_initial(&a1,1);
  fa_set_state_initial(&a1,2);
  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_add_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
  }
  EXPECT_TRUE(a1.state_count == 3);
  // Suppressions d'états non valide
  fa_remove_state(&a1,-3);
  EXPECT_TRUE(a1.state_count == 3);
  fa_remove_state(&a1,10);
  EXPECT_TRUE(a1.state_count == 3);
  // Suppressions de tous les états 1 par 1
  fa_remove_state(&a1,0);
  EXPECT_TRUE(a1.state_count == 2);
  fa_remove_state(&a1,1);
  EXPECT_TRUE(a1.state_count == 1);
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
  EXPECT_TRUE(!fa_is_deterministic(&a1));
  fa_destroy(&a1);
}

TEST(fa,isComplete){
  struct fa a1;
  fa_create(&a1,2,2);
  EXPECT_TRUE(!fa_is_complete(&a1));
  fa_add_transition(&a1,0,'a', 0);
  EXPECT_TRUE(!fa_is_complete(&a1));
  fa_add_transition(&a1,0,'a', 1);
  EXPECT_TRUE(!fa_is_complete(&a1));
  fa_add_transition(&a1,0,'b', 1);
  EXPECT_TRUE(!fa_is_complete(&a1));
  fa_add_transition(&a1,1,'a', 0);
  EXPECT_TRUE(!fa_is_complete(&a1));
  fa_add_transition(&a1,1,'b', 1);
  EXPECT_TRUE(fa_is_complete(&a1));
  fa_destroy(&a1);
}

TEST(fa,makeComplete){
  struct fa a1;
  fa_create(&a1,2,3);
  EXPECT_TRUE(!fa_is_complete(&a1));
  fa_make_complete(&a1);
  EXPECT_TRUE(fa_is_complete(&a1));
  fa_destroy(&a1);
}

TEST(fa,createGraphNotInverted){
  struct fa a1;
  struct graph g1;
  fa_create(&a1,6,10);
	fa_set_state_initial(&a1,0);
  fa_set_state_initial(&a1,8);
  fa_set_state_initial(&a1,6);
  fa_set_state_initial(&a1,4);
	fa_set_state_final(&a1, 1);
  fa_set_state_final(&a1, 8);
  fa_set_state_final(&a1, 6);
  fa_set_state_final(&a1, 4);

  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_add_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
  }

  graph_create_from_fa(&g1,&a1,false);
  graph_destroy(&g1);
  fa_destroy(&a1);
}
TEST(fa,createGraphInverted){
  struct fa a1;
  struct graph g1;
  fa_create(&a1,6,10);
	fa_set_state_initial(&a1,0);
  fa_set_state_initial(&a1,8);
  fa_set_state_initial(&a1,6);
  fa_set_state_initial(&a1,4);
	fa_set_state_final(&a1, 1);
  fa_set_state_final(&a1, 8);
  fa_set_state_final(&a1, 6);
  fa_set_state_final(&a1, 4);

  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_add_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
  }

  graph_create_from_fa(&g1,&a1,true);
  graph_destroy(&g1);
  fa_destroy(&a1);
}

TEST(fa,graphPrinting){
  struct fa a1;
  struct graph g1;
  fa_create(&a1,6,10);
	fa_set_state_initial(&a1,0);
  fa_set_state_initial(&a1,8);
  fa_set_state_initial(&a1,6);
  fa_set_state_initial(&a1,4);
	fa_set_state_final(&a1, 1);
  fa_set_state_final(&a1, 8);
  fa_set_state_final(&a1, 6);
  fa_set_state_final(&a1, 4);

  for(size_t nbAlph=0;nbAlph<3;nbAlph++){
    for(size_t nbState=0;nbState<4;nbState++){
      for(size_t nbState1=0;nbState1<4;nbState1++){
        fa_add_transition(&a1,nbState,'a'+nbAlph,nbState1);
      }
    }
  }

  graph_create_from_fa(&g1,&a1,true);
  graph_pretty_print(&g1,stdout);
  graph_destroy(&g1);
  fa_destroy(&a1);

}

TEST(fa,languageIsEmpty){
  struct fa a1;
  fa_create(&a1,6,10);
  EXPECT_TRUE(fa_is_language_empty(&a1));
  fa_set_state_final(&a1,2);
  fa_set_state_initial(&a1,0);
  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,1,'b',2);
  EXPECT_TRUE(!fa_is_language_empty(&a1));
  fa_destroy(&a1);
}

TEST(fa,removeNonAccessible){
  struct fa a1;
  fa_create(&a1,6,10);
  fa_set_state_final(&a1,2);
  fa_set_state_initial(&a1,0);
  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,1,'b',2);
  fa_remove_non_accessible_states(&a1);
  // seuls etats accessible : 0 1 et 2
  EXPECT_TRUE(fa_count_transitions(&a1)==2);
  EXPECT_TRUE(a1.state_count==3);
  fa_destroy(&a1);
}

TEST(fa,removeNonCoAccessible){
  struct fa a1;
  fa_create(&a1,6,10);
  fa_set_state_final(&a1,2);
  fa_set_state_initial(&a1,0);
  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,1,'b',2);
  fa_remove_non_co_accessible_states(&a1);
  // seul etats co accessible 0 1 et 2
  EXPECT_TRUE(fa_count_transitions(&a1)==2);
  EXPECT_TRUE(a1.state_count==3);
  fa_destroy(&a1);
}

TEST(fa,faProduct){
  struct fa a1;
  fa_create(&a1,2,2);
  fa_set_state_final(&a1,1);
  fa_set_state_initial(&a1,0);
  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,1,'b',1);
  fa_add_transition(&a1,1,'a',1);

  struct fa a2;
	fa_create(&a2, 2, 2);

	fa_add_transition(&a2, 0, 'a', 0);
	fa_add_transition(&a2, 0, 'b', 1);
	fa_add_transition(&a2, 1, 'b', 1);
	fa_add_transition(&a2, 1, 'a', 0);

	fa_set_state_initial(&a2, 0);
	fa_set_state_final(&a2, 1);

	struct fa a3;
	fa_create_product(&a3, &a2, &a1);
  // faire la verification d'avoir le bon automate
  fa_pretty_print(&a3,stdout);
  EXPECT_TRUE(a3.state_count==3);
  EXPECT_TRUE(fa_count_transitions(&a3)==5);
  EXPECT_TRUE(is_initial(&a3,0));
  EXPECT_TRUE(is_final(&a3,2));
  fa_destroy(&a1);
	fa_destroy(&a2);
	fa_destroy(&a3);
}

TEST(fa,deterministic){
  struct fa a1;
  fa_create(&a1,2,3);
  fa_set_state_final(&a1,1);
  fa_set_state_initial(&a1,0);
  fa_set_state_initial(&a1,1);
  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,0,'a',0);
  fa_add_transition(&a1,1,'a',2);

  fa_add_transition(&a1,1,'b',0);
  fa_add_transition(&a1,1,'b',1);
  fa_add_transition(&a1,1,'b',2);

  fa_add_transition(&a1,2,'a',0);
  fa_add_transition(&a1,2,'b',1);
  fa_add_transition(&a1,2,'b',2);
  EXPECT_TRUE(!fa_is_deterministic(&a1));

  struct fa a2;
  fa_create_deterministic(&a2,&a1);
  fa_pretty_print(&a2,stdout);
  EXPECT_TRUE(fa_is_deterministic(&a2));

  fa_destroy(&a1);
	fa_destroy(&a2);
}

TEST(fa,isIncluded){
  struct fa a1;
  fa_create(&a1,2,3);
  fa_set_state_final(&a1,1);
  fa_set_state_initial(&a1,0);
  fa_set_state_initial(&a1,1);
  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,0,'a',0);
  fa_add_transition(&a1,1,'a',2);

  fa_add_transition(&a1,1,'b',0);
  fa_add_transition(&a1,1,'b',1);
  fa_add_transition(&a1,1,'b',2);

  fa_add_transition(&a1,2,'a',0);
  fa_add_transition(&a1,2,'b',1);
  fa_add_transition(&a1,2,'b',2);

  EXPECT_TRUE(fa_is_included(&a1,&a1));
  fa_destroy(&a1);
}

TEST(fa,Minimisation0){
  struct fa a1;
  fa_create(&a1,2,4);
  fa_set_state_initial(&a1,0);
  fa_set_state_final(&a1,3);

  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,0,'a',2);
  fa_add_transition(&a1,0,'b',1);
  fa_add_transition(&a1,0,'b',2);

  fa_add_transition(&a1,1,'a',3);
  fa_add_transition(&a1,2,'a',3);
  fa_add_transition(&a1,1,'b',3);
  fa_add_transition(&a1,2,'b',3);

  struct fa a2;
  fa_create_minimal_nerode(&a2,&a1);

  EXPECT_TRUE(fa_count_transitions(&a1)==4);
  EXPECT_TRUE(a1.state_count == 3);
  EXPECT_TRUE(is_initial(&a1,0));
  EXPECT_TRUE(is_final(&a1,0));

  fa_destroy(&a2);
  fa_destroy(&a1);


}

TEST(fa,Minimisation1){
  struct fa a1;
  fa_create(&a1,2,6);
  fa_set_state_initial(&a1,0);
  fa_set_state_final(&a1,3);
  fa_set_state_final(&a1,4);

  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,0,'b',2);
  fa_add_transition(&a1,1,'b',3);
  fa_add_transition(&a1,1,'a',2);
  fa_add_transition(&a1,2,'a',1);
  fa_add_transition(&a1,2,'b',4);
  fa_add_transition(&a1,3,'a',4);
  fa_add_transition(&a1,3,'b',5);
  fa_add_transition(&a1,4,'a',3);
  fa_add_transition(&a1,4,'b',5);
  fa_add_transition(&a1,5,'a',5);
  fa_add_transition(&a1,5,'b',5);


  struct fa a2;
  fa_create_minimal_nerode(&a2,&a1);

  EXPECT_TRUE(fa_count_transitions(&a1)==8);
  EXPECT_TRUE(a1.state_count == 4);
  EXPECT_TRUE(is_initial(&a1,0));
  EXPECT_TRUE(is_final(&a1,2));

  fa_destroy(&a2);
  fa_destroy(&a1);
}

TEST(fa,Minimisation2){
  struct fa a1;
  fa_create(&a1,2,3);
  fa_set_state_initial(&a1,0);
  fa_set_state_initial(&a1,1);
  fa_set_state_final(&a1,2);

  fa_add_transition(&a1,0,'a',1);
  fa_add_transition(&a1,1,'a',2);
  fa_add_transition(&a1,0,'b',1);
  fa_add_transition(&a1,1,'b',2);
  struct fa a2;
  fa_create_minimal_nerode(&a2,&a1);

  EXPECT_TRUE(fa_count_transitions(&a1)==4);
  EXPECT_TRUE(a1.state_count == 4);
  EXPECT_TRUE(is_initial(&a1,0));
  EXPECT_TRUE(is_final(&a1,2));

  fa_destroy(&a2);
  fa_destroy(&a1);
}

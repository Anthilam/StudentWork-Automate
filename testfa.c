// BOISSON Romain - GUY Timothée

#include "fa.h"

// Test de la fonction fa_create
void test_fa_create(void) {
	struct fa a;
	fa_create(&a, 4, 5);

	fa_destroy(&a);
}

// Test de la fonction fa_destroy_
void test_fa_destroy(void) {
	struct fa a;
	fa_create(&a, 4, 5);
	fa_destroy(&a);
}

// Test de la fonction fa_set_state_initial
void test_fa_set_state_initial(void) {
	struct fa a;
	fa_create(&a, 4, 5);

	fa_set_state_initial(&a, 1);

	fa_destroy(&a);
}

// Test de la fonction fa_set_state_final
void test_fa_set_state_final(void) {
	struct fa a;
	fa_create(&a, 4, 5);

	fa_set_state_final(&a, 1);

	fa_destroy(&a);
}

// Test de la fonction fa_add_transition
void test_fa_add_transition(void) {
	struct fa a;
	fa_create(&a, 4, 5);
}

int main() {
	//CU_TestRegistry* CU_pTestRegistry;
	//CU_initialize_registry();

	struct fa a1;
	fa_create(&a1, 2, 5);

	fa_add_transition(&a1, 0, 'a', 1);
	fa_add_transition(&a1, 0, 'a', 2);
	fa_add_transition(&a1, 0, 'a', 3);

	fa_add_transition(&a1, 1, 'b', 3);

	fa_add_transition(&a1, 2, 'a', 3);
	fa_add_transition(&a1, 2, 'b', 4);

	fa_add_transition(&a1, 3, 'a', 3);
	fa_add_transition(&a1, 3, 'b', 4);
	fa_add_transition(&a1, 3, 'a', 3);
	fa_add_transition(&a1, 3, 'b', 4);
	fa_add_transition(&a1, 3, 'a', 1);

	fa_add_transition(&a1, 3, 'a', 5);
	fa_add_transition(&a1, 3, 'a', 2);
	fa_add_transition(&a1, 3, 'b', 2);

	fa_add_transition(&a1, 4, 'a', 4);

	fa_set_state_initial(&a1,0);
	fa_set_state_initial(&a1,1);
	fa_set_state_final(&a1, 1);
	fa_set_state_final(&a1, 4);

	fa_pretty_print(&a1, stdout);

	printf("transitions nb = %lu\n\n", fa_count_transitions(&a1));

<<<<<<< HEAD
	fa_remove_state(&a1, 0);
	fa_remove_state(&a1, 1);
	fa_remove_state(&a1, 2);
	fa_remove_state(&a1, 3);
	fa_remove_state(&a1, 4);

	fa_pretty_print(&a1, stdout);

	printf("transitions nb = %lu\n\n", fa_count_transitions(&a1));

	fa_destroy(&a1);

	struct fa a2;
	fa_create(&a2, 2, 5);

	fa_add_transition(&a2, 0, 'a', 1);
	fa_add_transition(&a2, 0, 'b', 2);

	fa_add_transition(&a2, 1, 'b', 3);
	fa_add_transition(&a2, 1, 'a', 2);

	fa_add_transition(&a2, 2, 'a', 3);


	fa_add_transition(&a2,4,'a',4);
	fa_add_transition(&a2,4,'b',2);
	fa_set_state_initial(&a2,0);

	fa_set_state_final(&a2, 1);
	fa_set_state_final(&a2, 4);


	printf("a2 : \n");
	fa_pretty_print(&a2, stdout);

	if( fa_is_deterministic(&a2) ==true ){
=======
	if(fa_is_deterministic(&a1) ){
>>>>>>> cd7635df55e7b7167bb22ce0d9b6cb3307ca7d35
		printf("l'automate est déterministe \n");
	}else{
		printf("l'automate n'est pas déterministe \n");
	}

<<<<<<< HEAD
	if( fa_is_complete(&a2) ==true){
		printf("l'automate est complet \n");
	}else{
		printf("l'automate n'est pas complet \n");
	}

	fa_make_complete(&a2);
	printf("a2 : \n");
	printf("apres make_complete \n");
	fa_pretty_print(&a2, stdout);

	if( fa_is_deterministic(&a2) ==true ){
		printf("l'automate est déterministe \n");
	}else{
		printf("l'automate n'est pas déterministe \n");
	}

	if( fa_is_complete(&a2) ==true){
		printf("l'automate est complet \n");
	}else{
		printf("l'automate n'est pas complet \n");
	}
	fa_destroy(&a2);
=======
	fa_destroy(&a1);
>>>>>>> cd7635df55e7b7167bb22ce0d9b6cb3307ca7d35
}

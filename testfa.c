// BOISSON Romain - GUY Timothée

#include "fa.h"
#include <CUnit/CUnit.h>

// Test de la fonction fa_create
void test_fa_create(void) {
	struct fa a;
	fa_create(&a, 4, 5);

	CU_ASSERT_TRUE(a.alpha_count == 4);
	CU_ASSERT_TRUE(a.state_count == 5);
	CU_ASSERT_FALSE(a.state_array == NULL)

	fa_destroy(&a);
}

// Test de la fonction fa_destroy_
void test_fa_destroy(void) {
	struct fa a;
	fa_create(&a, 4, 5);
	fa_destroy(&a);

	CU_ASSERT_TRUE(a.state_array == NULL);
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
	fa_create(&a1, 4, 4);

	fa_add_transition(&a1, 0, 'a', 1);
	fa_add_transition(&a1, 1, 'b', 3);
	fa_add_transition(&a1, 2, 'c', 0);
	fa_add_transition(&a1, 2, 'c', 1);
	fa_add_transition(&a1, 3, 'c', 2);

	fa_set_state_initial(&a1,1);
	fa_set_state_initial(&a1, 3);
	fa_set_state_final(&a1, 2);
	fa_set_state_final(&a1, 0);

	fa_pretty_print(&a1, stdout);

	printf("transitions nb = %lu\n", fa_count_transitions(&a1));

	fa_destroy(&a1);
}

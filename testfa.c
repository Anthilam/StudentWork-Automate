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
	CU_TestRegistry* CU_pTestRegistry;
	CU_initialize_registry();

	printf("Hello world!\n");
}

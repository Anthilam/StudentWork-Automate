// BOISSON Romain - GUY Timothée

#include "fa.h"
#include <CUnit/CUnit.h>

void test_fa_create(void) {
	struct fa a;

	fa_create(&a, 4, 5);

	CU_ASSERT_TRUE(a.alpha_count == 4);
	CU_ASSERT_TRUE(a.state_count == 5);
	CU_ASSERT_FALSE(a.state_array == NULL)

	fa_destroy(&a);
}

void test_fa_set_state_initial(void) {
	struct fa a;

	fa_create(&a, 4, 5);

	CU_ASSERT_TRUE(a.state_array[1] != NULL);

	fa_set_state_initial(&a, 1);

	CU_ASSERT_TRUE(a.state_array[1].is_initial);
	CU_ASSERT_FALSE(a.state_array[1].is_final);

	fa_destroy(&a);
}

void test_fa_set_state_final(void) {
	struct fa a;

	fa_create(&a, 4, 5);

	CU_ASSERT_TRUE(a.state_array[1] != NULL);

	fa_set_state_final(&a, 1);

	CU_ASSERT_TRUE(a.state_array[1].is_final);
	CU_ASSERT_FALSE(a.state_array[1].is_initial);

	fa_destroy(&a);
}

void test_fa_add_transition(void) {
	struct fa a;

	fa_create(&a, 4, 5);


}


int main() {
	printf("Hello world!\n");
}

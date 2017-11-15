// BOISSON Romain - GUY Timothée

#include "fa.h"

int main() {
	/*
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

	fa_add_transition(&a1, 4, 'a', 4);

	fa_set_state_initial(&a1,0);
	fa_set_state_initial(&a1,1);
	fa_set_state_final(&a1, 1);
	fa_set_state_final(&a1, 4);

	fa_pretty_print(&a1, stdout);

	struct graph ga1;
	graph_create_from_fa(&ga1, &a1, false);
	graph_pretty_print(&ga1, stdout);

	bool b = fa_is_language_empty(&a1);
	if (b == true) {
		printf("\nLe langage est vide\n");
	}
	else {
		printf("\nLe langage est non-vide\n");
	}

	fa_remove_non_co_accessible_states(&a1);
	fa_pretty_print(&a1, stdout);

	fa_destroy(&a1);
	graph_destroy(&ga1);
	*/

	struct fa A;
	fa_create(&A, 2, 3);

	fa_add_transition(&A, 0, 'a', 1);
	fa_add_transition(&A, 1, 'a', 0);
	fa_add_transition(&A, 1, 'b', 2);
	fa_add_transition(&A, 2, 'b', 2);

	fa_set_state_initial(&A, 0);
	fa_set_state_final(&A, 2);

	struct fa B;
	fa_create(&B, 4, 3);

	fa_add_transition(&B, 0, 'a', 1);
	fa_add_transition(&B, 1, 'a', 2);
	fa_add_transition(&B, 1, 'b', 2);
	fa_add_transition(&B, 2, 'b', 1);

	fa_set_state_initial(&B, 0);
	fa_set_state_initial(&B, 1);
	fa_set_state_final(&B, 2);

	struct fa C;
	fa_create_product(&C, &A, &B);

	fa_pretty_print(&C, stdout);

	if (fa_has_empty_intersection(&A, &B)) {
		printf("L'intersection est vide\n");
	}
	else {
		printf("L'intersection est non-vide\n");
	}

	fa_destroy(&A);
	fa_destroy(&B);
	fa_destroy(&C);
}

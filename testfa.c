// BOISSON Romain - GUY Timothée

#include "fa.h"

int main() {
	/*struct fa a1;
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

	fa_destroy(&a1);

	*/

	/*struct fa A;
	fa_create(&A, 2, 2);

	fa_add_transition(&A, 0, 'a', 1);
	fa_add_transition(&A, 1, 'a', 1);
	fa_add_transition(&A, 1, 'b', 1);

	fa_set_state_initial(&A, 0);
	fa_set_state_final(&A, 1);

	struct fa B;
	fa_create(&B, 2, 2);

	fa_add_transition(&B, 0, 'a', 0);
	fa_add_transition(&B, 0, 'b', 1);
	fa_add_transition(&B, 1, 'b', 1);
	fa_add_transition(&B, 1, 'a', 0);

	fa_set_state_initial(&B, 0);
	fa_set_state_final(&B, 1);

	struct fa C;
	fa_create_product(&C, &A, &B);

	fa_pretty_print(&A, stdout);
	fa_pretty_print(&B, stdout);
	fa_pretty_print(&C, stdout);

	if (fa_is_included(&A, &A)) {
		printf("\nL'automate est inclus dans l'autre automate\n");
	}
	else {
		printf("\nL'automate n'est pas inclus dans l'autre automate\n");
	}

	if (fa_is_included(&A, &B)) {
		printf("\nL'automate est inclus dans l'autre automate\n");
	}
	else {
		printf("\nL'automate n'est pas inclus dans l'autre automate\n");
	}

	fa_destroy(&A);
	fa_destroy(&B);
	fa_destroy(&C);
	*/

	struct fa A;
	fa_create(&A, 2, 5);

	fa_add_transition(&A, 0, 'b', 1);
	fa_add_transition(&A, 0, 'a', 2);
	fa_add_transition(&A, 0, 'b', 2);
	fa_add_transition(&A, 0, 'a', 3);

	fa_add_transition(&A, 1, 'b', 4);

	fa_add_transition(&A, 2, 'b', 1);
	fa_add_transition(&A, 2, 'a', 2);
	fa_add_transition(&A, 2, 'b', 2);
	fa_add_transition(&A, 2, 'a', 3);

	fa_add_transition(&A, 3, 'a', 4);

	fa_add_transition(&A, 4, 'a', 4);
	fa_add_transition(&A, 4, 'b', 4);

	fa_set_state_initial(&A, 0);
	fa_set_state_final(&A, 4);

	fa_pretty_print(&A, stdout);

	printf("\n---------------------------------------\n\n");

	struct fa A_det;
	fa_create_deterministic(&A_det, &A);

	fa_pretty_print(&A_det, stdout);

	printf("Adet det ? %d\n", fa_is_deterministic(&A_det));

	printf("Adet C Adet ? %d\n", fa_is_included(&A_det, &A_det));

	printf("Adet 0 == 0 ? %d\n", fa_are_nerode_equivalent(&A_det, 0, 0));

	printf("Adet 0 == 2 ? %d\n", fa_are_nerode_equivalent(&A_det, 0, 2));

	struct fa max;
	fa_create(&max, 3, 4);

	fa_add_transition(&max, 0, 'a', 1);
	fa_add_transition(&max, 0, 'b', 2);
	fa_add_transition(&max, 1, 'c', 3);
	fa_add_transition(&max, 2, 'c', 3);

	fa_set_state_initial(&max, 0);
	fa_set_state_final(&max, 3);

	struct fa min;

	fa_create_minimal_nerode(&min, &max);

	fa_pretty_print(&max, stdout);
	fa_pretty_print(&min, stdout);

	fa_destroy(&A);
	fa_destroy(&A_det);
	fa_destroy(&min);
	fa_destroy(&max);
}

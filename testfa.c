// BOISSON Romain - GUY Timothée

#include "fa.h"

int main() {
	/*// automate mini romain
	struct fa A;
	fa_create(&A, 2, 3);

	fa_add_transition(&A, 0, 'a', 1);
	fa_add_transition(&A, 0, 'b', 1);
	fa_add_transition(&A, 0, 'a', 2);
	fa_add_transition(&A, 0, 'b', 2);

	fa_set_state_initial(&A, 0);
	fa_set_state_final(&A, 1);
	fa_set_state_final(&A, 2);

	fa_pretty_print(&A, stdout);

	struct fa A_det;

	fa_create_deterministic(&A_det, &A);

	fa_pretty_print(&A_det, stdout);

	struct fa A_min;

	fa_create_minimal_nerode(&A_min, &A);

	fa_pretty_print(&A_min, stdout);

	fa_destroy(&A);
	fa_destroy(&A_det);
	fa_destroy(&A_min);*/

	/*// automate deja minimal diapo 220
	struct fa A;
	fa_create(&A, 2, 3);

	fa_set_state_initial(&A, 0);
	fa_set_state_final(&A, 1);

	fa_add_transition(&A, 0, 'a', 1);
	fa_add_transition(&A, 0, 'b', 0);
	fa_add_transition(&A, 1, 'a', 2);
	fa_add_transition(&A, 1, 'b', 1);
	fa_add_transition(&A, 2, 'a', 2);
	fa_add_transition(&A, 2, 'b', 0);

	fa_pretty_print(&A, stdout);

	struct fa A_min;

	fa_create_minimal_nerode(&A_min, &A);

	fa_pretty_print(&A_min, stdout);

	fa_destroy(&A);
	fa_destroy(&A_min);*/

	/*// Produit sujet internet
	struct fa A;
	fa_create(&A, 2, 3);

	fa_set_state_initial(&A, 0);
	fa_set_state_final(&A, 2);

	fa_add_transition(&A, 0, 'a', 1);
	fa_add_transition(&A, 1, 'a', 0);
	fa_add_transition(&A, 1, 'b', 2);
	fa_add_transition(&A, 2, 'b', 2);

	struct fa B;
	fa_create(&B, 2, 3);

	fa_set_state_initial(&B, 0);
	fa_set_state_initial(&B, 1);
	fa_set_state_final(&B, 2);

	fa_add_transition(&B, 0, 'a', 1);
	fa_add_transition(&B, 1, 'a', 2);
	fa_add_transition(&B, 1, 'b', 2);
	fa_add_transition(&B, 2, 'b', 1);

	struct fa prod;
	fa_create_product(&prod, &A, &B);

	fa_pretty_print(&A, stdout);
	fa_pretty_print(&B, stdout);
	fa_pretty_print(&prod, stdout);

	fa_destroy(&A);
	fa_destroy(&B);
	fa_destroy(&prod);*/

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

	fa_destroy(&min);
	fa_destroy(&max);

	struct fa A;
	fa_create(&A, 2, 6);

	fa_set_state_initial(&A, 1);
	fa_set_state_final(&A, 1);
	fa_set_state_final(&A, 3);

	fa_add_transition(&A, 0, 'a', 0);
	fa_add_transition(&A, 0, 'b', 1);
	fa_add_transition(&A, 1, 'a', 3);
	fa_add_transition(&A, 1, 'b', 2);
	fa_add_transition(&A, 2, 'a', 4);
	fa_add_transition(&A, 2, 'b', 0);
	fa_add_transition(&A, 3, 'a', 3);
	fa_add_transition(&A, 3, 'b', 4);
	fa_add_transition(&A, 4, 'a', 2);
	fa_add_transition(&A, 4, 'b', 5);
	fa_add_transition(&A, 5, 'a', 5);
	fa_add_transition(&A, 5, 'b', 3);

	fa_pretty_print(&A, stdout);

	struct fa A_min;
	fa_create_minimal_nerode(&A_min, &A);

	fa_pretty_print(&A_min, stdout);

	fa_destroy(&A);
	fa_destroy(&A_min);
}

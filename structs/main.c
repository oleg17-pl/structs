#include "vector.h"
#include "list.h"
#include <stdio.h>

void vector_test(void) {
	vector_t vec = v_create();
	v_push_back(&vec, 1);
	v_print(&vec);
}

void list_test(void) {
	list_t *list = l_create();
	for (size_t i = 0; i < 9; i++) {
		l_push_back(list, i);
	}
	l_print(list);
	l_reverse(list);
	l_print(list);
	l_free(list);
	/*
	list_t *list = l_create(), *list2 = l_create();
	l_push_back(list, 1);
	l_push_back(list, 2);
	l_push_back(list, 3);

	l_push_back(list2, 4);
	l_push_back(list2, 3);
	l_push_back(list2, 2);
	l_push_back(list2, 1);

	l_print(list);
	l_print(list2);

	l_swap(list, list2);
	l_print(list);
	l_print(list2);
	*/
}

int main(void) {
	list_test();
	return 0;
}
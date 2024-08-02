#include "vector.h"
#include "list.h"
#include <stdio.h>

void vector_test(void) {
	vector_t vec = v_create();
	v_push_back(&vec, 1);
	v_print(&vec);
}

void list_test(void) {
	list_t list = l_create();

	l_push_back(&list, 10);
	l_push_back(&list, 20);
	l_push_back(&list, 30);
	l_push_back(&list, 40);
	l_push_back(&list, 50);
	l_push_back(&list, 60);
	l_print(&list);

	l_insert(&list, l_at(&list, 0), 100);
	l_print(&list);
}

int main(void) {
	list_test();
	return 0;
}
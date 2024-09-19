#include "vector.h"
#include "list.h"
#include <stdio.h>

void vector_test(void) {
	pvec_t vec = v_create();
	v_push_back(vec, 1);
	v_print(vec);
	v_free(vec);
}

void list_test(void) {
	plist_t list = l_create();
	l_insert(list, l_at(list, 0), 10);
	l_insert(list, l_at(list, 0), 20);
	l_insert(list, l_at(list, 0), 3);
	l_insert(list, l_at(list, 0), 4);
	l_print(list);
	l_free(list);
}

int main(void) {
	vector_test();
	return 0;
}
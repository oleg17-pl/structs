#include <stdlib.h>
#include <stdio.h>

#include "list.h"

static list_el_t *create_el(void) {
	return (list_el_t *)malloc(sizeof(list_el_t));
}

listtype_t el_value(const list_el_t *const el) {
	return el->value;
}

list_el_t *el_next(const list_el_t *const el) {
	return el->next;
}

list_el_t *el_prev(const list_el_t *const el) {
	return el->prev;
}

char l_empty(CONST_LIST_PARAM) {
	return list->first == NULL;
}

size_t l_size(CONST_LIST_PARAM) {
	return list->size;
}

list_el_t *l_begin(CONST_LIST_PARAM) {
	return list->first;
}

list_el_t *l_end(CONST_LIST_PARAM) {
	list_el_t *last = l_begin(list);
	if (last != NULL) {
		while (last->next != NULL) {
			last = el_next(last);
		}
	}
	return last;
}

list_el_t *l_at(CONST_LIST_PARAM, size_t index) {
	if (index >= l_size(list)) {
		return l_end(list);
	}
	list_el_t *el = l_begin(list);
	for (size_t i = 0; i < index; i++) {
		el = el->next;
	}
	return el;
}

listtype_t l_front(CONST_LIST_PARAM) {
	return l_empty(list) ? 0 : el_value(l_begin(list));
}

listtype_t l_back(CONST_LIST_PARAM) {
	return l_empty(list) ? 0 : el_value(l_end(list));
}

void l_insert(LIST_PARAM, list_el_t *const el, listtype_t val) {
	list_el_t *new_el = create_el();
	new_el->value = val;
	if (l_empty(list)) {
		list->first = new_el;
		new_el->prev = NULL;
		new_el->next = NULL;
	}
	else {
		if (el == NULL) {
			return;
		}
		if (el == l_begin(list)) {
			list->first = new_el;
			new_el->prev = el->prev;
			new_el->next = el;
			el->prev = new_el;
		}
		else {
			new_el->next = el;
			new_el->prev = el_prev(el);
			if (el_prev(el) != NULL) {
				el->prev->next = new_el;
			}
			el->prev = new_el;
		}
	}
	list->size++;
}

void l_push_back(LIST_PARAM, listtype_t val) {
	if (!l_empty(list)) {
		list_el_t *last = l_end(list), *new_el = create_el();
		new_el->value = val;
		new_el->next = el_next(last);
		last->next = new_el;
		last->next = new_el;
		if (el_next(last) != NULL) {
			last->next->prev = new_el;
		}
		new_el->prev = last;
	}
	else {
		list->first = create_el();
		list_el_t *frst = l_begin(list);
		frst->value = val;
		frst->prev = NULL;
		frst->next = NULL;
	}
	list->size++;
}

void l_push_front(LIST_PARAM, listtype_t val) {
	/*
	list_el_t *new_first = create_el();
	new_first->value = val;
	new_first->prev = NULL;
	new_first->next = list->first;
	if (list->first != NULL) {
		l_begin(list)->prev = new_first;
	}
	list->first = new_first;
	*/
	l_insert(list, l_begin(list), val);
}

void l_erase(LIST_PARAM, list_el_t *el) {
	if (el == NULL) {
		return;
	}
	list_el_t *prev_el = el_prev(el), *next_el = el_next(el);
	if (prev_el != NULL) {
		prev_el->next = next_el;
	}
	if (next_el != NULL) {
		next_el->prev = prev_el;
	}
	if (el == l_begin(list)) {
		list->first = next_el;
	}
	free(el);
	list->size--;
}

void l_pop_back(LIST_PARAM) {
	/*
	if (empty(list)) {
		return;
	}
	list_el_t *last = end(list);
	if (last->prev != NULL) {
		last->prev->next = NULL;
	}
	if (last == list->first) {
		list->first = NULL;
	}
	free(last);
	*/
	l_erase(list, l_end(list));
}

void l_pop_front(LIST_PARAM) {
	/*
	if (empty(list)) {
		return;
	}
	list_el_t *first = begin(list);
	if (first->next != NULL) {
		first->next->prev = NULL;
	}
	list->first = first->next;
	free(first);
	*/
	l_erase(list, l_begin(list));
}

// chat gpt wrote
void l_swapels(LIST_PARAM, list_el_t *const el1, list_el_t *const el2) {
	if (el1 == el2 || el1 == NULL || el2 == NULL) {
		return;
	}

	if (el1->next == el2) {
		el1->next = el_next(el2);
		el2->prev = el_prev(el1);
		el2->next = el1;
		el1->prev = el2;

		if (el1->next != NULL) {
			el1->next->prev = el1;
		}
		if (el2->prev != NULL) {
			el2->prev->next = el2;
		}
	}
	else if (el2->next == el1) {
		el2->next = el_next(el1);
		el1->prev = el_prev(el2);
		el1->next = el2;
		el2->prev = el1;

		if (el2->next != NULL) {
			el2->next->prev = el2;
		}
		if (el1->prev != NULL) {
			el1->prev->next = el1;
		}
	}
	else {
		list_el_t *tmp_next = el_next(el1);
		list_el_t *tmp_prev = el_prev(el1);

		el1->next = el_next(el2);
		el1->prev = el_prev(el2);
		el2->next = tmp_next;
		el2->prev = tmp_prev;

		if (el1->next != NULL) {
			el1->next->prev = el1;
		}
		if (el1->prev != NULL) {
			el1->prev->next = el1;
		}
		if (el2->next != NULL) {
			el2->next->prev = el2;
		}
		if (el2->prev != NULL) {
			el2->prev->next = el2;
		}
	}

	if (list->first == el1) {
		list->first = el2;
	}
	else if (list->first == el2) {
		list->first = el1;
	}
}

void l_swap(LIST_PARAM, LIST_PARAM_2) {
	list_el_t *tmp_el = l_begin(list);
	size_t tmp_size = list->size;
	list->first = l_begin(list2);
	list2->first = tmp_el;
	list->size = list2->size;
	list2->size = tmp_size;
}

void l_reverse(LIST_PARAM) {
	size_t n = l_size(list);
	if (n == 1 || n == 0) {
		return;
	}
	for (size_t i = 0; i < n; i++) {
		if (i == (int)(n / 2)) {
			break;
		}
		size_t b = n - i - 1;
		list_el_t *front_el = l_at(list, i);
		list_el_t *back_el = l_at(list, b);
		l_swapels(list, front_el, back_el);
	}
}

char l_isless(listtype_t a, listtype_t b) {
	return a < b;
}

char l_isgreater(listtype_t a, listtype_t b) {
	return a > b;
}

void l_sort(LIST_PARAM, comp_t comp) {
	if (comp == NULL) {
		comp = l_isless;
	}
	// selection algorithm
	size_t n = l_size(list);
	for (size_t i = 0; i < n - 1; i++) {
		size_t target_index = i;
		for (size_t el = i + 1; el < n; el++) {
			list_el_t *check = l_at(list, el);
			list_el_t *target = l_at(list, target_index);
			if (comp(el_value(check), el_value(target))) {
				target_index = el;
			}
		}
		if (target_index != i) {
			l_swapels(list, l_at(list, target_index), l_at(list, i));
		}
	}
}

list_t *l_create(void) {
	list_t *list = (list_t *)malloc(sizeof(list_t));
	if (list == NULL) {
		return NULL;
	}
	list->first = NULL;
	list->size = 0;
	return list;
}

void l_clear(LIST_PARAM) {
	while (!l_empty(list)) {
		l_pop_back(list);
	}
	list->size = 0;
}

void l_free(LIST_PARAM) {
	l_clear(list);
	free(list);
}

void l_print(CONST_LIST_PARAM) {
	size_t n = l_size(list);
	printf("***\n");
	if (n != 0) {
		printf("list info: size: %u\n\n", n);
		for (size_t i = 0; i < n; i++) {
			printf("index: %i; value: %i\n", i, el_value(l_at(list, i)));
		}
	}
	else {
		printf("list is empty\n");
	}
	printf("***\n\n");
}
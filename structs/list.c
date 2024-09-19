#include <stdlib.h>
#include <stdio.h>

#include "list.h"

static l_iterator_t create_node(void) {
	return (l_iterator_t)malloc(sizeof(l_node_t));
}

listtype_t l_iter_value(const_l_iterator_t iter) {
	return iter->value;
}

l_iterator_t l_iter_next(const_l_iterator_t iter) {
	return iter->next;
}

l_iterator_t l_iter_prev(const_l_iterator_t iter) {
	return iter->prev;
}

bool_t l_empty(CONST_LIST_PARAM) {
	return list->head == NULL;
}

size_t l_size(CONST_LIST_PARAM) {
	return list->size;
}

l_iterator_t l_begin(CONST_LIST_PARAM) {
	return list->head;
}

l_iterator_t l_end(CONST_LIST_PARAM) {
	l_iterator_t last = l_begin(list);
	if (last != NULL) {
		while (last->next != NULL) {
			last = l_iter_next(last);
		}
	}
	return last;
}

l_iterator_t l_at(CONST_LIST_PARAM, size_t index) {
	if (index >= l_size(list)) {
		return l_end(list);
	}
	l_iterator_t iter = l_begin(list);
	for (size_t i = 0; i < index; i++) {
		iter = l_iter_next(iter);
	}
	return iter;
}

listtype_t l_front(CONST_LIST_PARAM) {
	return l_empty(list) ? 0 : l_iter_value(l_begin(list));
}

listtype_t l_back(CONST_LIST_PARAM) {
	return l_empty(list) ? 0 : l_iter_value(l_end(list));
}

void l_insert(LIST_PARAM, l_iterator_t iter, listtype_t val) {
	l_iterator_t new_node = create_node();
	new_node->value = val;
	if (l_empty(list)) {
		list->head = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else {
		if (iter == NULL) {
			return;
		}
		if (iter == l_begin(list)) {
			list->head = new_node;
			new_node->prev = l_iter_prev(iter);
			new_node->next = iter;
			iter->prev = new_node;
		}
		else {
			new_node->next = iter;
			new_node->prev = l_iter_prev(iter);
			if (l_iter_prev(iter) != NULL) {
				iter->prev->next = new_node;
			}
			iter->prev = new_node;
		}
	}
	list->size++;
}

void l_push_back(LIST_PARAM, listtype_t val) {
	if (!l_empty(list)) {
		l_iterator_t last = l_end(list), new_node = create_node();
		new_node->value = val;
		new_node->next = l_iter_next(last);
		last->next = new_node;
		last->next = new_node;
		if (l_iter_next(last) != NULL) {
			last->next->prev = new_node;
		}
		new_node->prev = last;
	}
	else {
		list->head = create_node();
		l_iterator_t head = l_begin(list);
		head->value = val;
		head->prev = NULL;
		head->next = NULL;
	}
	list->size++;
}

void l_push_front(LIST_PARAM, listtype_t val) {
	l_insert(list, l_begin(list), val);
}

void l_erase(LIST_PARAM, l_iterator_t iter) {
	if (iter == NULL) {
		return;
	}
	l_iterator_t prev_node = l_iter_prev(iter), next_node = l_iter_next(iter);
	if (prev_node != NULL) {
		prev_node->next = next_node;
	}
	if (next_node != NULL) {
		next_node->prev = prev_node;
	}
	if (iter == l_begin(list)) {
		list->head = next_node;
	}
	free(iter);
	list->size--;
}

void l_pop_back(LIST_PARAM) {
	l_erase(list, l_end(list));
}

void l_pop_front(LIST_PARAM) {
	l_erase(list, l_begin(list));
}

// chat gpt wrote
void l_swapels(LIST_PARAM, l_iterator_t const iter1, l_iterator_t const iter2) {
	if (iter1 == iter2 || iter1 == NULL || iter2 == NULL) {
		return;
	}

	if (iter1->next == iter2) {
		iter1->next = l_iter_next(iter2);
		iter2->prev = l_iter_prev(iter1);
		iter2->next = iter1;
		iter1->prev = iter2;

		if (iter1->next != NULL) {
			iter1->next->prev = iter1;
		}
		if (iter2->prev != NULL) {
			iter2->prev->next = iter2;
		}
	}
	else if (iter2->next == iter1) {
		iter2->next = l_iter_next(iter1);
		iter1->prev = l_iter_prev(iter2);
		iter1->next = iter2;
		iter2->prev = iter1;

		if (iter2->next != NULL) {
			iter2->next->prev = iter2;
		}
		if (iter1->prev != NULL) {
			iter1->prev->next = iter1;
		}
	}
	else {
		l_iterator_t tmp_next = l_iter_next(iter1);
		l_iterator_t tmp_prev = l_iter_prev(iter1);

		iter1->next = l_iter_next(iter2);
		iter1->prev = l_iter_prev(iter2);
		iter2->next = tmp_next;
		iter2->prev = tmp_prev;

		if (iter1->next != NULL) {
			iter1->next->prev = iter1;
		}
		if (iter1->prev != NULL) {
			iter1->prev->next = iter1;
		}
		if (iter2->next != NULL) {
			iter2->next->prev = iter2;
		}
		if (iter2->prev != NULL) {
			iter2->prev->next = iter2;
		}
	}

	if (list->head == iter1) {
		list->head = iter2;
	}
	else if (list->head == iter2) {
		list->head = iter1;
	}
}

void l_swap(LIST_PARAM, LIST_PARAM_2) {
	l_iterator_t tmp_node = l_begin(list);
	size_t tmp_size = list->size;
	list->head = l_begin(list2);
	list2->head = tmp_node;
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
		l_iterator_t front_node = l_at(list, i);
		l_iterator_t back_node = l_at(list, b);
		l_swapels(list, front_node, back_node);
	}
}

bool_t l_isless(listtype_t a, listtype_t b) {
	return a < b;
}

bool_t l_isgreater(listtype_t a, listtype_t b) {
	return a > b;
}

void l_sort(LIST_PARAM, compfunc_t compfunc) {
	if (compfunc == NULL) {
		compfunc = l_isless;
	}
	// selection algorithm
	size_t n = l_size(list);
	for (size_t i = 0; i < n - 1; i++) {
		size_t target_index = i;
		for (size_t nd = i + 1; nd < n; nd++) {
			l_iterator_t check = l_at(list, nd);
			l_iterator_t target = l_at(list, target_index);
			if (compfunc(l_iter_value(check), l_iter_value(target))) {
				target_index = nd;
			}
		}
		if (target_index != i) {
			l_swapels(list, l_at(list, target_index), l_at(list, i));
		}
	}
}

plist_t l_create(void) {
	plist_t list = (plist_t)malloc(sizeof(list_t));
	if (list == NULL) {
		return NULL;
	}
	list->head = NULL;
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
			printf("index: %i; value: %i\n", i, l_iter_value(l_at(list, i)));
		}
	}
	else {
		printf("list is empty\n");
	}
	printf("***\n\n");
}
/*

Copyright (c) 2005-2008, Simon Howard

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

 */

/* ArrayList test cases */

#include <stdio.h>
#include <assert.h>
#include "test-arrayList.h"
#include "alloc-testing.h"
#include "framework.h"

#include "../structure/arrayList.h"

int variable1, variable2, variable3, variable4;

ArrayList *generate_arrayList(void) {
    ArrayList *arrayList;
    arrayList = arrayList_init();
    arrayList_append(arrayList,&variable1);
    arrayList_append(arrayList,&variable2);
    arrayList_append(arrayList,&variable3);
    arrayList_append(arrayList,&variable4);
	return arrayList;
}

void test_arrayList_new_free(void) {
	ArrayList *arrayList;

	/* Normal allocated */
	arrayList = arrayList_init();
	assert(arrayList != NULL);
	arrayList_destroy(arrayList);

	/* Freeing a null arraylist works */
	arrayList_destroy(NULL);

	/* Test low memory scenarios (failed malloc) */

	alloc_test_set_limit(0);
	arrayList = arrayList_init();
	assert(arrayList == NULL);

	alloc_test_set_limit(1);
	arrayList = arrayList_init();
	assert(arrayList == NULL);
	arrayList_destroy(arrayList);
}

void test_arrayList_append(void) {
	ArrayList *arrayList;
	int i;

	arrayList = arrayList_init();

	assert(arrayList->length == 0);

	/* Append some entries */

	assert(arrayList_append(arrayList, &variable1) == 0);
	assert(arrayList->length == 1);

	assert(arrayList_append(arrayList, &variable2) == 0);
	assert(arrayList->length == 2);

	assert(arrayList_append(arrayList, &variable3) == 0);
	assert(arrayList->length == 3);

	assert(arrayList_append(arrayList, &variable4) == 0);
	assert(arrayList->length == 4);

	assert(arrayList->data[0] == &variable1);
	assert(arrayList->data[1] == &variable2);
	assert(arrayList->data[2] == &variable3);
	assert(arrayList->data[3] == &variable4);

	/* Test appending many entries */
	for (i=0; i<10000; ++i) {
		assert(arrayList_append(arrayList, NULL) == 0);
	}

	arrayList_destroy(arrayList);

	/* Test low memory scenario */
	arrayList = arrayList_init();
	alloc_test_set_limit(0);

	for (i=0; i<100; ++i) {
		assert(arrayList_append(arrayList, NULL) == 0);
	}

	assert(arrayList->length == 100);
	assert(arrayList_append(arrayList, NULL) == 0);
	assert(arrayList->length == 101);

	arrayList_destroy(arrayList);
}

void test_arrayList_sort(void) {
	ArrayList *arraylist;
	int entries[] = { 89, 4, 23, 42, 4, 16, 15, 4, 8, 99, 50, 30, 4 };
	int sortedUp[]  = { 4, 4, 4, 4, 8, 15, 16, 23, 30, 42, 50, 89, 99 };
	int sortedDown[]  = { 99, 89, 50, 42, 30, 23, 16, 15, 8, 4, 4, 4, 4 };
	unsigned int num_entries = sizeof(entries) / sizeof(int);
	unsigned int i;

	arraylist = arrayList_init();

	for (i=0; i<num_entries; ++i) {
		arrayList_append(arraylist, (ArrayListValueEntry) entries[i]);
	}

    arrayList_sort(arraylist, 0);
	/* List length is unchanged */
	assert(arraylist->length == num_entries);

	/* Check the list is sorted by asc */
	for (i=0; i<num_entries; ++i) {
        int value = (int) arraylist->data[i];
		assert(value == sortedUp[i]);
	}

    arrayList_sort(arraylist, 1);
    /* List length is unchanged */
    assert(arraylist->length == num_entries);

    /* Check the list is sorted by desc */
    for (i=0; i<num_entries; ++i) {
        int value = (int) arraylist->data[i];
        assert(value == sortedDown[i]);
    }
    arrayList_destroy(arraylist);

	/* Check sorting an empty list */

	arraylist = arrayList_init();
	arrayList_sort(arraylist, 0);
	assert(arraylist->length == 0);
	arrayList_destroy(arraylist);

	/* Check sorting a list with 1 entry */

	arraylist = arrayList_init();

	arrayList_append(arraylist, &entries[0]);
	arrayList_sort(arraylist, 0);

	assert(arraylist->length == 1);
	assert(arraylist->data[0] == &entries[0]);

	arrayList_destroy(arraylist);
}

static UnitTestFunction tests[] = {
	test_arrayList_new_free,
	test_arrayList_append,
	test_arrayList_sort,
	NULL
};

int arrayListTest() {
	variable1 = 1;
	variable2 = 5;
	variable3 = 20;
	variable4 = 7;

	run_tests(tests);
	return 0;
}


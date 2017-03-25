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

/* LinkListEntry test cases */

#include <stdio.h>
#include <assert.h>
#include "test-linkList.h"
#include "alloc-testing.h"
#include "framework.h"

#include "../structure/linkList.h"

int variable1, variable2, variable3, variable4;

int linkList_compare_test(LinkListValue value1, LinkListValue value2){
    if (value1 == value2){
        return 0;
    }else if (value1 > value2) return 1;
    else if (value1 < value2) return -1;
}

LinkListEntry *generate_LinkListEntry(void) {
	LinkListEntry* linkList = linkList_initList();
    linkList_appendNode(linkList, &variable1);
    linkList_appendNode(linkList, &variable2);
    linkList_appendNode(linkList, &variable3);
    linkList_appendNode(linkList, &variable4);
	return linkList;
}

void test_LinkListEntry_new_free(void) {
    LinkListEntry *LinkListEntry;

	/* Normal allocated */
	LinkListEntry = linkList_initList();
	assert(LinkListEntry != NULL);
	linkList_destroy(LinkListEntry);

	/* Freeing a null LinkListEntry works */
	linkList_destroy(NULL);

	/* Test low memory scenarios (failed malloc) */

	alloc_test_set_limit(0);
	LinkListEntry = linkList_initList();
	assert(LinkListEntry == NULL);

	alloc_test_set_limit(1);
	LinkListEntry = linkList_initList();
	assert(LinkListEntry != NULL);
	linkList_destroy(LinkListEntry);
}

void test_linkList_appendNode(void) {
	LinkListEntry *linkList;
	int i;

	linkList = linkList_initList();

	assert(linkList_getLength(linkList) == 0);

	/* Append some entries */

	assert(linkList_appendNode(linkList, &variable1));
	assert(linkList_getLength(linkList) == 1);

	assert(linkList_appendNode(linkList, &variable2));
	assert(linkList_getLength(linkList) == 2);

	assert(linkList_appendNode(linkList, &variable3));
	assert(linkList_getLength(linkList) == 3);

	assert(linkList_appendNode(linkList, &variable4));
	assert(linkList_getLength(linkList) == 4);

	assert(linkList_getIndexEntryByIndex(linkList,0)->data == &variable1);
	assert(linkList_getIndexEntryByIndex(linkList,1)->data == &variable2);
	assert(linkList_getIndexEntryByIndex(linkList,2)->data == &variable3);
	assert(linkList_getIndexEntryByIndex(linkList,3)->data == &variable4);

	/* Test appending many entries */
	for (i=0; i<10000; ++i) {
		assert(linkList_appendNode(linkList, NULL));
	}

	linkList_destroy(linkList);

	/* Test low memory scenario */
	linkList = linkList_initList();
	alloc_test_set_limit(0);

	for (i=0; i<100; ++i) {
		assert(!linkList_appendNode(linkList, NULL));
	}

	assert(linkList_getLength(linkList) == 0);
	assert(!linkList_appendNode(linkList, NULL));
	assert(linkList_getLength(linkList) == 0);

	linkList_destroy(linkList);
}

void test_LinkListEntry_sort(void) {
	LinkListEntry *linkList;
	int entries[] = { 89, 4, 23, 42, 4, 16, 15, 4, 8, 99, 50, 30, 4 };
	int sortedUp[]  = { 4, 4, 4, 4, 8, 15, 16, 23, 30, 42, 50, 89, 99 };
	int sortedDown[]  = { 99, 89, 50, 42, 30, 23, 16, 15, 8, 4, 4, 4, 4 };
	unsigned int num_entries = sizeof(entries) / sizeof(int);
	unsigned int i;

	linkList = linkList_initList();

	for (i=0; i<num_entries; ++i) {
		linkList_appendNode(linkList, entries[i]);
	}

    linkList_sort(linkList, 0, linkList_compare_test);
	/* List length is unchanged */
	assert(linkList_getLength(linkList) == num_entries);

	/* Check the list is sorted by asc */
	for (i=0; i<num_entries; ++i) {
        int value = (int) linkList_getIndexEntryByIndex(linkList, i)->data;
        assert(value == sortedUp[i]);
	}

    linkList_sort(linkList, 1, linkList_compare_test);
    /* List length is unchanged */
    assert(linkList_getLength(linkList) == num_entries);

    /* Check the list is sorted by desc */
    for (i=0; i<num_entries; ++i) {
        int value = (int) linkList_getIndexEntryByIndex(linkList, i)->data;
        assert(value == sortedDown[i]);
    }
    linkList_destroy(linkList);

	/* Check sorting an empty list */

	linkList = linkList_initList();
    linkList_sort(linkList, 0, linkList_compare_test);
	assert(linkList_getLength(linkList) == 0);
	linkList_destroy(linkList);

	/* Check sorting a list with 1 entry */

	linkList = linkList_initList();

	linkList_appendNode(linkList, entries[0]);
    linkList_sort(linkList, 0, linkList_compare_test);

	assert(linkList_getLength(linkList) == 1);
	assert(linkList_getIndexEntryByIndex(linkList, 0)->data == entries[0]);

	linkList_destroy(linkList);
}

static UnitTestFunction tests[] = {
	test_LinkListEntry_new_free,
	test_linkList_appendNode,
	test_LinkListEntry_sort,
	NULL
};

int linkListTest() {
	variable1 = 1;
	variable2 = 5;
	variable3 = 20;
	variable4 = 7;

	run_tests(tests);
	return 0;
}


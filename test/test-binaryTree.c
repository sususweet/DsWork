//
// Created by tangyq on 2017/3/27.
//

#include <assert.h>
#include <stdio.h>
#include "../structure/binaryTree.h"
#include "test-binaryTree.h"
#include "alloc-testing.h"

void test_bi_tree_new(void) {
    BinaryTree * tree = binaryTree_init();
    int a = 10, b = 3;
    BinaryTreeNode * rootNode = binaryTree_insert(tree, &a, NULL, BITREE_NODE_LEFT);
    BinaryTreeNode * rightNode = binaryTree_insert(tree, &b, rootNode, BITREE_NODE_RIGHT);
    assert(tree->nodeNum == 2);
    assert(*(int *)(tree->rootNode->value) == a);
    assert(*(int *)(rightNode->value) == b);
    binaryTree_removeNode(tree, rightNode);
    assert(tree->nodeNum == 1);
    binaryTree_destroy(tree);
}

int binaryTreeTest(){
    //test_bi_tree_new();
    BinaryTree * tree = binaryTree_init();
    int a = 10, b = 3;
    BinaryTreeNode * rootNode = binaryTree_insert(tree, 10, NULL, BITREE_NODE_LEFT);
    BinaryTreeNode * rightNode = binaryTree_insert(tree, 3, rootNode, BITREE_NODE_RIGHT);
    BinaryTreeNode * leftNode = binaryTree_insert(tree, 2, rootNode, BITREE_NODE_LEFT);
    binaryTree_insert(tree, 11, leftNode, BITREE_NODE_LEFT);
    binaryTree_insert(tree, 5, leftNode, BITREE_NODE_RIGHT);
    binaryTree_insert(tree, 1, rightNode, BITREE_NODE_RIGHT);
    binaryTree_preOrderNode(tree->rootNode);
    printf("\n\n");
    binaryTree_inOrderNode(tree->rootNode);
    printf("\n\n");
    binaryTree_postOrderNode(tree->rootNode);
    binaryTree_destroy(tree);

    assert(alloc_test_get_allocated() == 0);
}
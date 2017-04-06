//
// Created by tangyq on 2017/3/27.
//

#ifndef PROJECT1_BINARYTREE_H
#define PROJECT1_BINARYTREE_H

#ifdef __cplusplus
extern "C" {
#endif

/* 二叉树的左、右孩子标记 */
typedef enum {
    BITREE_NODE_LEFT = 0,
    BITREE_NODE_RIGHT = 1
} BinaryTreeNodeSide;

typedef struct _BinaryTree BinaryTree;  /* 二叉树结构 */
typedef struct _BinaryTreeNode BinaryTreeNode;  /* 二叉树节点 */
typedef void* BinaryTreeValue;  /* 二叉树中存储的数据 */
#define BITREE_NULL ((void *) 0)    /* 二叉树的空指针数据 */

/*采用三叉链表存储的二叉树*/
struct _BinaryTreeNode {
    BinaryTreeNode* children[2];
    BinaryTreeNode* parent;
    BinaryTreeValue value;
};

struct _BinaryTree {
    BinaryTreeNode *rootNode;   /* 根节点 */
    unsigned int nodeNum;   /* 节点数 */
};

BinaryTree* binaryTree_init();

void binaryTree_destroy(BinaryTree* binaryTree);

BinaryTreeNode* binaryTree_insert(BinaryTree* binaryTree, BinaryTreeValue value,
                                  BinaryTreeNode* parent, BinaryTreeNodeSide side);

int binaryTree_removeNode(BinaryTree* binaryTree, BinaryTreeNode* node);

BinaryTreeNode* binaryTree_root_node(BinaryTree* binaryTree);

BinaryTreeValue binaryTree_node_value(BinaryTreeNode* node);

BinaryTreeNode* binaryTree_node_child(BinaryTreeNode* node, BinaryTreeNodeSide side);

BinaryTreeNode* binaryTree_node_parent(BinaryTreeNode* node);

void binaryTree_preOrderNode(BinaryTreeNode* node);

void binaryTree_inOrderNode(BinaryTreeNode* node);

void binaryTree_postOrderNode(BinaryTreeNode* node);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_BINARYTREE_H

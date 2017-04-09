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

/**
 * @desc 初始化二叉树
 * @return 二叉树表地址
 */
BinaryTree* binaryTree_init();
/**
 * @desc 销毁二叉树
 * @param binaryTree 二叉树表地址
 */
void binaryTree_destroy(BinaryTree* binaryTree);
/**
 * @desc 向二叉树插入新节点
 * @param binaryTree 二叉树表地址
 * @param value 节点的值
 * @param parent 要插入的父节点
 * @param side 要插入的方向
 * @return binaryTree 插入的节点地址
 */
BinaryTreeNode* binaryTree_insert(BinaryTree* binaryTree, BinaryTreeValue value,
                     BinaryTreeNode* parent, BinaryTreeNodeSide side);
/**
 * @desc 从二叉树删除节点
 * @param binaryTree 二叉树表地址
 * @param node 要删除的节点地址
 * @return 0 删除成功，非0 删除失败
 */
int binaryTree_removeNode(BinaryTree* binaryTree, BinaryTreeNode* node);
/**
 * @desc 获取子节点
 * @param node 父节点地址
 * @param side 子节点方向
 * @return 子节点地址
 */
BinaryTreeNode* binaryTree_node_child(BinaryTreeNode* node, BinaryTreeNodeSide side);
/**
 * @desc 先序遍历二叉树
 * @param node 二叉树根节点地址
 */
void binaryTree_preOrderNode(BinaryTreeNode* node);
/**
 * @desc 中序遍历二叉树
 * @param node 二叉树根节点地址
 */
void binaryTree_inOrderNode(BinaryTreeNode* node);
/**
 * @desc 后序遍历二叉树
 * @param node 二叉树根节点地址
 */
void binaryTree_postOrderNode(BinaryTreeNode* node);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_BINARYTREE_H

//
// Created by tangyq on 2017/3/27.
//

#include <stdlib.h>
#include <stdio.h>
#include "binaryTree.h"

/*检查是否成功申请内存*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

BinaryTree* binaryTree_init(){
    BinaryTree* binaryTree = NULL;
    binaryTree = (BinaryTree*) malloc(sizeof(BinaryTree));
    Asert(binaryTree);
    binaryTree->rootNode = NULL;
    binaryTree->nodeNum = 0;
    return binaryTree;
}

static void binaryTree_destroy_subTree(BinaryTree* binaryTree, BinaryTreeNode* treeNode){
    if (treeNode == NULL) return;
    binaryTree_destroy_subTree(binaryTree, treeNode->children[BITREE_NODE_LEFT]);
    binaryTree_destroy_subTree(binaryTree, treeNode->children[BITREE_NODE_RIGHT]);
    free(treeNode);
    binaryTree->nodeNum--;
}

void binaryTree_destroy(BinaryTree* binaryTree){
    /*使用函数递归销毁节点及其所有的子树*/
    binaryTree_destroy_subTree(binaryTree, binaryTree->rootNode);
    /*销毁树表结构*/
    free(binaryTree);
}

static BinaryTreeNode* binaryTree_initNode(BinaryTreeValue value){
    BinaryTreeNode* newNode;
    newNode = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
    Asert(newNode);
    newNode -> value = value;
    newNode -> parent = NULL;
    newNode -> children[BITREE_NODE_LEFT] = NULL;
    newNode -> children[BITREE_NODE_RIGHT] = NULL;
    return newNode;
}

BinaryTreeNode* binaryTree_insert(BinaryTree* binaryTree, BinaryTreeValue value,
                                  BinaryTreeNode* parent, BinaryTreeNodeSide side){

    BinaryTreeNode* newNode = binaryTree_initNode(value);
    Asert(newNode);

    if (!(side == BITREE_NODE_LEFT || side == BITREE_NODE_RIGHT))
        return NULL;

    if (parent == NULL){
        binaryTree->rootNode = newNode;
        if (!binaryTree->rootNode){
            binaryTree->rootNode->parent = newNode;
            newNode->children[side] = binaryTree->rootNode;
            binaryTree->rootNode = newNode;
        }
    }else{
        if (parent->children[side]){
            parent->children[side]->parent = newNode;
        }
        newNode->parent = parent;
        newNode->children[side] = parent->children[side];
        parent->children[side] = newNode;
    }

    binaryTree->nodeNum++;
    return newNode;
}

int binaryTree_removeNode(BinaryTree* binaryTree, BinaryTreeNode* node){
    if (!node) return -1;
    BinaryTreeNode* parent = node->parent;
    if (!parent){
        binaryTree->rootNode = NULL;
    }else {
        if (parent->children[BITREE_NODE_LEFT] == node){
            parent->children[BITREE_NODE_LEFT] = NULL;
        }else if (parent->children[BITREE_NODE_RIGHT] == node){
            parent->children[BITREE_NODE_RIGHT] = NULL;
        }
    }
    binaryTree_destroy_subTree(binaryTree, node);
    return 0;
}

BinaryTreeNode* binaryTree_node_child(BinaryTreeNode* node, BinaryTreeNodeSide side){
    if (side == BITREE_NODE_LEFT || side == BITREE_NODE_RIGHT){
        return node->children[side];
    }else return NULL;
}

void binaryTree_preOrderNode(BinaryTreeNode* node){
    if (!node) return;
    //printf("%d\n", (int) node->value);
    printf("%c", *((char*)node->value));
    binaryTree_preOrderNode(node->children[BITREE_NODE_LEFT]);
    binaryTree_preOrderNode(node->children[BITREE_NODE_RIGHT]);
}

void binaryTree_inOrderNode(BinaryTreeNode* node){
    if (!node) return;
    binaryTree_inOrderNode(node->children[BITREE_NODE_LEFT]);
    //printf("%d\n", (int) node->value);
    printf("%s", (char*)node->value);
    binaryTree_inOrderNode(node->children[BITREE_NODE_RIGHT]);
}

void binaryTree_postOrderNode(BinaryTreeNode* node){
    if (!node) return;
    binaryTree_postOrderNode(node->children[BITREE_NODE_LEFT]);
    binaryTree_postOrderNode(node->children[BITREE_NODE_RIGHT]);
    printf("%c", *((char*)node->value));
    //printf("%d\n", (int) node->value);
}
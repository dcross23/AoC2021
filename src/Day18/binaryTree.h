#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char BinaryTreeElement;

typedef struct BinaryTreeNode{
	BinaryTreeElement info;
	struct BinaryTreeNode *left, *right;
	struct BinaryTreeNode *parent;
}BinaryTreeNode;

typedef BinaryTreeNode* BinaryTree;

BinaryTree createBTree(char *str);
BinaryTree createBinaryTreeNode(BinaryTreeElement info);
BinaryTree addTrees(BinaryTree t1, BinaryTree t2);
void reduceTree(BinaryTree t);
bool explosions(BinaryTree t, int depth, bool end);
bool splits(BinaryTree t, bool continueSplits);
int treeMagnitude(BinaryTree t);

#endif

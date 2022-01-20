#include "binaryTree.h"

#define CHAR_TO_NUM(c) (c-'0')
#define NUM_TO_CHAR(n) (n+'0')
 
BinaryTree createBTree(char *str){
	if(strlen(str) == 0) 
		return NULL;

	else if(strlen(str)==1 && str[0]>='0' && str[0]<='9' ){
		return createBinaryTreeNode(str[0]);
	}

	char leftstr[70]="";
	char rightstr[70]="";

	//Parse string and divide into left and right
	char stack[10];
	int stackTop = 0;
	stack[stackTop++] = str[0];
	bool checkingLeft = true;
	for(int i=1; i<strlen(str); i++){
		if(str[i]==',' && stackTop == 1){
			checkingLeft = false;
			continue;
		}

		if(str[i] == '[') stack[stackTop++] = str[i];
		else if(str[i] == ']') stackTop--;

		if(stackTop == 0) break;

		if(checkingLeft) strncat(leftstr, &str[i],1);
		else strncat(rightstr, &str[i],1);	
	}

	//Parse childs recursively
	BinaryTree t = createBinaryTreeNode('.');
	t->left = createBTree(leftstr);
	t->left->parent = t;
	t->right = createBTree(rightstr);
	t->right->parent = t;
	return t;
}


BinaryTree createBinaryTreeNode(BinaryTreeElement info){
	BinaryTreeNode *new;

	if((new = malloc(sizeof(BinaryTreeNode))) == NULL){
		#ifdef DEBUG
			fprintf(stderr,"ERROR: can not create tree node\n");	
		#endif	
		return NULL;
	}else{
		new->info = info;
		new->left = new->right = NULL;
		new->parent = NULL;
		return new;
	}
}

BinaryTree addTrees(BinaryTree t1, BinaryTree t2){
	if(t1 == NULL || t2 == NULL)
		return NULL;

	BinaryTree t = createBinaryTreeNode('.');
	t->left = t1;
	t1->parent = t;
	t->right = t2;
	t2->parent = t;
	return t;
}

int treeMagnitude(BinaryTree t){
	if(t->info == '.'){
		int res = (3*treeMagnitude(t->left) + 2*treeMagnitude(t->right));
		return res;
	}else{	
		return CHAR_TO_NUM(t->info);
	}
}

void reduceTree(BinaryTree t){
	//Explosions until finishes
	if(explosions(t, 0, false)){
		reduceTree(t);
	}

	//Splits and then continue if not finish
	if(splits(t, false)){
		reduceTree(t);
	}

} 

bool explosions(BinaryTree t, int depth, bool continueExplosions){
	if(continueExplosions) 
		return true;

	if(t->info == '.'){
		if(depth < 4){
			bool cont = explosions(t->left , depth+1, continueExplosions);
			if(!cont)
				cont = explosions(t->right, depth+1, continueExplosions);
			return cont;
		
		}else{
			BinaryTree prev = t, curr = t->parent;
			//Get right most node if exists (left node of left child)
			while(curr != NULL && (curr->left == NULL || curr->left == prev)){
				prev = curr;
				curr = curr->parent;	
			}

			if(curr != NULL){
				curr = curr->left;
				while(curr->info == '.'){
					if(curr->right != NULL)
						curr = curr->right;
					else
						curr = curr->left;
				}

				curr->info += CHAR_TO_NUM(t->left->info);
			}

			//Get left most node if exists (right node of right child)
			prev = t; curr = t->parent;
			while(curr != NULL && (curr->right == NULL || curr->right == prev)){
				prev = curr;
				curr = curr->parent;	
			}

			if(curr != NULL){
				curr = curr->right;
				while(curr->info == '.'){
					if(curr->left != NULL)
						curr = curr->left;
					else
						curr = curr->right;
				}

				curr->info += CHAR_TO_NUM(t->right->info);
			}

			//Explode node
			t->info = '0';
			t->left = NULL;
			t->right = NULL;
			return true;
		}

	}
	return false;
}

bool splits(BinaryTree t, bool continueSplits){
	if(continueSplits) 
		return true;

	if(t->info == '.'){
		bool cont = splits(t->left , continueSplits);
		if(!cont)
			cont = splits(t->right, continueSplits);
		return cont;
	
	}else if(CHAR_TO_NUM(t->info)>=10){
		int value = CHAR_TO_NUM(t->info);
		t->info = '.';
		t->left = createBinaryTreeNode(NUM_TO_CHAR(value / 2));
		t->left->parent = t;
		t->right = createBinaryTreeNode(NUM_TO_CHAR(value - value/2));
		t->right->parent = t;
		return true;

	}else
		return false;
}




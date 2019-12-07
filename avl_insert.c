// AVL tree implementation for insertion
#include<stdio.h>
#include<stdlib.h>





// An AVL tree node

typedef struct Node
{
	int key;
	struct Node *left, *right;
	int height;
}Node;


// height of the tree

int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// 
// Maximum of two integers
int max(int a, int b)
{
	if(a>b)
		return a;
    else
		return b;

}

// Function to create a new node with the given 
//key as an argument and returns the pointer to the new node.
Node* newNode(int key)
{
	Node* node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially
					// added at leaf
	return(node);
}

// right rotation
Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left),
					height(y->right)) + 1;
	x->height = max(height(x->left),
					height(x->right)) + 1;

	// Return new root
	return x;
}

// left rotation
Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left),
					height(x->right)) + 1;
	y->height = max(height(y->left),
					height(y->right)) + 1;

	// Return new root
	return y;
}

// Height difference of the left and right subtree of the node N.
int h_diff(Node *N)
{
	if (N == NULL)
		return 0;
	return(height(N->left) - height(N->right));
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, int key)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // Equal keys are not allowed in BST
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
						height(node->right));

	/* 3. get the height difference */
	int balance = h_diff(node);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Case 1
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Case 2
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Case 3
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Case 4
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

// function to print inorder

void inOrder(Node *root)
{
	if(root != NULL)
	{
		inOrder(root->left);
		printf("(%d @ %p left:%p right:%p)\n", root->key, root,root->left,root->right);
		inOrder(root->right);
	}
}

int main(void)
{
	int key;
	Node *root = NULL;
	printf("Enter zero to terminate\n");
	while(10)
		{

			printf("Enter the key value:");
			scanf("%d",&key);
			if(key == 0)
				break;

			
			root = insert(root, key);


			
		}
	inOrder(root);

	return 0;
}

//Name: Sanyam Gupta
//Roll number: 17089
//Course: MTH-307


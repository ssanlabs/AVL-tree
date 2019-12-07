// AVL tree implementation 
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

// Maximum of two integers
int max(int a, int b)
{
	if(a>b)
		return a;
    else
		return b;

}
//Function which creatres a new node with the given key 
//as an argument and returns the pointer to the new node.
Node* newNode(int key)
{
	Node* node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; //height is 1, because it is initially added to the leaf
	return(node);
}
//right rotation
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

// Height difference between the two subtrees(left-right)
int h_diff(Node *N)
{
	if (N == NULL)
		return 0;
	return(height(N->left) - height(N->right));
}

// function to insert a key
// in the subtree rooted with node and
// returns the n ew root of the subtree.
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

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = h_diff(node);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// case 1
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

Node * minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, int key)
{

    // STEP 1: We first simply perform the BST delete
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            
            root->key = temp->key;

            
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE HEIGHT DIFFERENCE OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = h_diff(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Case 1
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Case 2
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Case 3
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Case 4
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void inOrder(Node *root)
{
	if(root != NULL)
	{
		inOrder(root->left);
		printf("(Node: (%d @ %p) left child:(%d @ %p) right child:(%d @ %p))\n", root->key, root,root->left->key,root->left,root->right->key,root->right);
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

			/* Constructing tree given in
			the above figure */
			root = insert(root, key);


		}
	inOrder(root);
	int del;
	printf("Enter the key value to be deleted:\t");
	scanf("%d",&del);
	if(del>0)
		deleteNode(root,del);
	printf("New AVL tree is:\n");
	inOrder(root);
	return 0;
}
//Name: Sanyam Gupta
//Roll number: 17089
//Course: MTH-307


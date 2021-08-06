#include <iostream>
#include <bits/stdc++.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

class Node {
	public:
	int key;
	Node *left;
	Node *right;
	int height;
};

int max(int a, int b) {
	return(a>b) ? a:b;
}


int height( Node *node) {
	if(node == NULL) return 0;
	return node->height;
}

Node* newNode(int key) {
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	
	return (node);
}

Node *rightRotate(Node *node) {
    Node *nodex = node->left;
    Node *T2 = nodex->right;
 
    nodex->right = node;
    node->left = T2;
 
    node->height = max(height(node->left),
                    height(node->right)) + 1;
    nodex->height = max(height(nodex->left),
                    height(nodex->right)) + 1;
 
    return nodex;
}

Node *leftRotate(Node *nodex) {
    Node *node = nodex->right;
    Node *T2 = node->left;
 
    node->left = nodex;
    nodex->right = T2;
 
    nodex->height = max(height(nodex->left),   
                    height(nodex->right)) + 1;
    node->height = max(height(node->left),
                    height(node->right)) + 1;
 
    return node;
}

int getBalance(Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else return node;
 
   
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    int balance = getBalance(node);
 
    
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
   
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    
    return node;
}


Node* findMinNode(Node* node) {
	Node* current = node;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
 
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
 
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
 
    else {
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;
 
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else *root = *temp; 
            free(temp);
        }
        else
        {
            Node* temp = findMinNode(root->right);
 			root->key = temp->key;
 
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }
 
    if (root == NULL)
    return root;
 
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    int balance = getBalance(root);
 
    
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);
 
    if (balance > 1 &&
        getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);
 
    if (balance < -1 &&
        getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}


int main() {
	
	 Node *root = NULL;
     
   
    root = insert(root, 16);
    root = insert(root, 19);
    root = insert(root, 22);
    root = insert(root, 45);
    root = insert(root, 57);
    root = insert(root, 30);
     
    
    cout << "The preoder of the AVL tree \n";
    preOrder(root);
    cout<<"\n";
    root = deleteNode(root, 45);
    preOrder(root);
    
    
	return 0;
}

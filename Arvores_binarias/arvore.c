#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node * left;
    struct node * right;
} Node;

int makeTree(Node ** root);
Node * createNode(int key_value);
int insertNode(Node ** leaf, int key_value);
int printTree(Node ** root);



int main()
{
    Node ** root;
    makeTree(root);
    insertNode(root, 10);
    printf("      %d       ", (*root)->value);

    /*insertNode(root, 5);
    printf("      %d       ", (*root)->value);*/

}

int makeTree(Node ** root)
{
    *root = NULL;
    return 1;
}

Node * createNode(int key_value)
{
    Node * newNode = (Node*) malloc (sizeof(Node));

    if(newNode == NULL)
        return NULL;
    newNode->value = key_value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int insertNode(Node ** leaf, int key_value)
{
    //Checking if the tree is empty
    if(*leaf == NULL)
    {
        *leaf = createNode(key_value);
    }
    else if(key_value < (*leaf)->value)
        insertNode(&(*leaf)->left, key_value);
    else
        insertNode(&(*leaf)->right, key_value);
}


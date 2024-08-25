#include "common.h"

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode Node;

Node createTree(Node node){
    char c;
    printf("input node value\n");
    scanf("%c", &c);
    getchar();
    node.val = atoi(&c);

    printf("create left node ? y or n\n");
    scanf("%c", &c);
    getchar();
    if(c == 'y'){
        node.left = (Node *)malloc(sizeof(Node));
        createTree(*node.left);
    }else{
        node.left = NULL;
    }

    printf("create right node ? y or n\n");
    scanf("%c", &c);
    getchar();
    if(c == 'y'){
        node.right = (Node *)malloc(sizeof(Node));
        createTree(*node.right);
    }else{
        node.right = NULL;
    }
    return node;
}

void traverse(Node *node){
    if(node == NULL)
        return;
    printf("%d \n", node->val);
    traverse(node->left);
    traverse(node->right);
}

int main(void){
    Node node;
    node = createTree(node);
    traverse(&node);
    exit(0);
}

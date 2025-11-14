#include "utils/ast.h"
#include "utils/token.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//tree functions
ASTTree* CreateASTTree(){
    ASTTree* tree = (ASTTree*)malloc(sizeof(ASTTree));
    tree->root = NULL;

    return tree;
}

void DeleteASTTree(ASTTree** tree){
    if(*tree == NULL)
        return;

    if((*tree)->root == NULL)
        return;

    //auxilerty stack to store all nodes in the tree to free
    ASTNode** NodeList = NULL;
    int NodeCount = 0;

    //find all nodes
    ASTListNode* list = NULL;
    GetTreesNodes((*tree)->root, &list);

    ASTListNode* currentNode = list; 
    while(currentNode != NULL){
        DeleteASTNode(&currentNode->node);
        currentNode = currentNode->next;
    }

    DeleteASTList(&list);

    free(*tree);
    *tree = NULL;
}

void GetTreesNodes(ASTNode* root, ASTListNode** list){
    //base case
    //if node is in list, return, O(N) search
    if(IsNodeInList(*list, root))
        return;
    
    //recursive case
    //else, add to list and check children
    ASTListNode* listNode = CreateASTListNode(root); 
    ASTListAppendNode(list, listNode);

    //check children
    for(int i = 0; i < root->ChildCount; i++){
        GetTreesNodes(root->Children[i], list);
    }
}
    

//ASTListNode functions
ASTListNode* CreateASTListNode(ASTNode* node){
    ASTListNode* newListNode = (ASTListNode*)malloc(sizeof(ASTListNode));
    newListNode->node = node;
    newListNode->next = NULL;

    return newListNode;
}

void DeleteASTList(ASTListNode** root){
    ASTListNode* currentNode = *root;
    while(currentNode != NULL){
        ASTListNode* next = currentNode->next;

        currentNode->next = NULL;
        currentNode->node = NULL;

        free(currentNode);

        currentNode = next;
    }

    *root = NULL;
}

void ASTListAppendNode(ASTListNode** list, ASTListNode* appendix){
    appendix->next = *list; 
    *list = appendix;
}

bool IsNodeInList(ASTListNode* list, ASTNode* node){
    ASTListNode* currentNode = list;
    while(currentNode != NULL){
        if(currentNode->node == node)
            return true;

        currentNode = currentNode->next;
    }

    return false;
}

//ASTNode functions
ASTNode* CreateASTNode(TokenType tokenType, unsigned char asciiValue){
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->TokenType = tokenType;

    node->AsciiValue = asciiValue; 

    node->Children = NULL;
    node->ChildCount = 0;
    
    return node;
}

void DeleteASTNode(ASTNode** node){
    (*node)->Children = NULL;
    (*node)->ChildCount = 0;

    free(*node);
    *node = NULL; 
}

void ASTNodeAddChild(ASTNode* parent, ASTNode* child){
    if(parent == NULL || child == NULL)
        return;

    int length = parent->ChildCount + 1;
    ASTNode** children = (ASTNode**)realloc(parent->Children, length * sizeof(ASTNode*));

    if(children == NULL){
        if(parent->Children == NULL)
            free(parent->Children);
    }
    else{
        parent->Children = children;
    }

    children[parent->ChildCount] = child;
    parent->ChildCount = length;
}

ASTNode* ASTGetChildNodeByValue(ASTNode* root, unsigned char value){
    if(root->Children == NULL)
        return NULL;

    for(int i = 0; i < root->ChildCount; i++){
        ASTNode* node = root->Children[i];
        if(node->AsciiValue == value)
            return root->Children[i];
    }

    return NULL;
}

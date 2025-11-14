#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include "utils/token.h"
#include <stdbool.h>

struct ASTNode;
struct ASTree;

struct ASTListNode;

typedef struct ASTNode{
    TokenType TokenType;

    unsigned char AsciiValue;

    struct ASTNode** Children; 
    int ChildCount;
} ASTNode;

typedef struct ASTListNode{
    ASTNode* node;
    struct ASTListNode* next;
} ASTListNode;

typedef struct ASTTree{
    ASTNode* root; 
} ASTTree;

//tree functions
ASTTree* CreateASTTree();
void DeleteASTTree(ASTTree**);
void GetTreesNodes(ASTNode* root, ASTListNode** list);

//ASTListNode functions
ASTListNode* CreateASTListNode(ASTNode* node);
void DeleteASTList(ASTListNode** root);
void ASTListAppendNode(ASTListNode** list, ASTListNode* appendix);
bool IsNodeInList(ASTListNode* list, ASTNode* node);

//ASTNode Functions
ASTNode* CreateASTNode(TokenType tokenType, unsigned char asciiValue);
void DeleteASTNode(ASTNode**);
void ASTNodeAddChild(ASTNode* parent, ASTNode* child);
ASTNode* ASTGetChildNodeByValue(ASTNode* root, unsigned char value);

#endif

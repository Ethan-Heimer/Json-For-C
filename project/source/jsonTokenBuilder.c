#include "json/jsonTokenBuilder.h"
#include "utils/ast.h"
#include "utils/token.h"

#include <stdlib.h>

bool ValidateToken(ASTNode** currentASTNode, char token){
        ASTNode* newNode = ASTGetChildNodeByValue(*currentASTNode, token);         

        if(newNode == NULL){
            return false;
        }

        *currentASTNode = newNode;
        return true;
};

void AddNumericCharactersToNode(ASTNode* parentNode, ASTNode** childNodes, int childCount){
    ASTListNode* newNodeList = NULL;

    ASTNode* decimalPoint = CreateASTNode(NUMBER_DATA, '.');

    //add numeric values
    for(int i = 0; i < 10; i++){ 
         ASTNode* node = CreateASTNode(NUMBER_DATA, '0'+i);
         ASTNodeAddChild(parentNode, node);

         for(int j = 0; j < childCount; j++)
            ASTNodeAddChild(node, childNodes[j]);

        ASTListNode* listNode = CreateASTListNode(node);
        ASTListAppendNode(&newNodeList, listNode);
    }
    
    //attach nodes to eachother
    int length = parentNode->ChildCount;
    ASTListNode* currentNode = newNodeList;
    while(currentNode != NULL){
        for(int i = 0; i < length; i++){ 
            ASTNodeAddChild(currentNode->node, parentNode->Children[i]);
        }

        currentNode = currentNode->next;
    }

    //add decimal node to number nodes
    for(int i = 0; i < length; i++)
        ASTNodeAddChild(decimalPoint, parentNode->Children[i]);
        
    DeleteASTList(&newNodeList); 
}

void AddAsciiToNode(ASTNode* parentNode, ASTNode** childNodes, int childCount){
    //add all (valid) ascii characters
    ASTListNode* newNodeList = NULL;
    for(unsigned char i = 0; i < '~'; i++){ 
        if(i == '"')
            continue;

        ASTNode* node = CreateASTNode(TEXT_DATA, i);
        ASTNodeAddChild(parentNode, node);

        for(int j = 0; j < childCount; j++)
            ASTNodeAddChild(node, childNodes[j]);

        ASTListNode* listNode = CreateASTListNode(node);
        ASTListAppendNode(&newNodeList, listNode);
    }

    //attach nodes to eachother
    int childLength = parentNode->ChildCount;
    ASTListNode* currentNode = newNodeList;

    while(currentNode != NULL){
        for(int i = 0; i < childLength; i++){ 
            ASTNodeAddChild(currentNode->node, parentNode->Children[i]);
        }

        currentNode = currentNode->next;
    }

    DeleteASTList(&newNodeList); 
}

void AddBooleanValues(ASTNode* parentNode, ASTNode** childNodes, int childCount){
    //true
    ASTNode* T = CreateASTNode(TEXT_DATA, 't');
    ASTNode* R = CreateASTNode(TEXT_DATA, 'r');
    ASTNode* U = CreateASTNode(TEXT_DATA, 'u');
    ASTNode* E = CreateASTNode(TEXT_DATA, 'e');

    //false
    ASTNode* F = CreateASTNode(TEXT_DATA, 'f');
    ASTNode* A = CreateASTNode(TEXT_DATA, 'a');
    ASTNode* L = CreateASTNode(TEXT_DATA, 'l');
    ASTNode* S = CreateASTNode(TEXT_DATA, 's');

    //connect true nodes
    ASTNodeAddChild(parentNode, T);
    ASTNodeAddChild(T, R);
    ASTNodeAddChild(R, U);
    ASTNodeAddChild(U, E);

    //connect false nodes
    ASTNodeAddChild(parentNode, F);
    ASTNodeAddChild(F, A);
    ASTNodeAddChild(A, L);
    ASTNodeAddChild(L, S);
    ASTNodeAddChild(S, E);

    //both share e at the end 
    for(int i = 0; i < childCount; i++){ 
        ASTNodeAddChild(E, childNodes[i]);
    }

}

void PushToken(Queue* queue, String* dataString, TokenType tokenType){
    Token* token = CreateToken(dataString->string, tokenType);
    Push(queue, token);

    ClearString(dataString);
}

bool DiscardToken(ASTNode* currentSyntaxNode){
    TokenType type = currentSyntaxNode->TokenType;

    return (type == QUOTE || type == PAIR);
}

void Tokenize(ASTNode* currentSyntaxNode, char currentChar, String* tokenString, Queue* queue, TokenizeType* tokenizeState){
    bool push = ChangeTokenizingState(currentSyntaxNode, tokenizeState);

    if(push) 
        PushToken(queue, tokenString, DATA); 

    if(!DiscardToken(currentSyntaxNode)){
        AppendChar(tokenString, currentChar);

        if(*tokenizeState == PUSH)
            PushToken(queue, tokenString, currentSyntaxNode->TokenType); 
    }
}

bool ChangeTokenizingState(ASTNode* currentSyntaxNode, TokenizeType* currentState){
    TokenType tokenType = currentSyntaxNode->TokenType;

    if(tokenType == TEXT_DATA || tokenType == NUMBER_DATA && *currentState == PUSH){
        *currentState = HOLD;
        return false;
    }

    if(*currentState == HOLD && tokenType != TEXT_DATA && tokenType != NUMBER_DATA){
        *currentState = PUSH;
        return true;
    }

    return false;
}

void UpdateScope(ASTNode* currentSyntaxNode, unsigned int* scope){
    TokenType tokenType = currentSyntaxNode->TokenType;
    if(tokenType == OPEN_ARRAY || tokenType == OPEN_OBJECT){
        *scope += 1;
        return;
    }

    if(tokenType == CLOSE_ARRAY || tokenType == CLOSE_OBJECT){
        *scope -= 1;
        return;
    }
}

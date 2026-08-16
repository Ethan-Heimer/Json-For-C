#include "json/jsonTokenBuilder.h"
#include "utils/ast.h"
#include "utils/token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool ValidateToken(ASTNode** currentASTNode, char token){
        ASTNode* newNode = ASTGetChildNodeByValue(*currentASTNode, token);         

        if(newNode == NULL){
            return false;
        }

        *currentASTNode = newNode;
        return true;
};

void AddNumericCharactersToNode(ASTNode* parentNode, ASTNode** childNodes, int childCount){
    ASTListNode* wholeNumberNumericNodes = NULL;
    ASTListNode* decimalNumberNumericNodes = NULL;
    ASTListNode* exponentNumberNumericNodes = NULL;

    ASTNode* decimalPoint = CreateASTNode(NUMBER_DATA, '.');

    ASTNode* positiveWhole = CreateASTNode(NUMBER_DATA, '+');
    ASTNode* negitiveWhole = CreateASTNode(NUMBER_DATA, '-');

    ASTNode* positiveExp = CreateASTNode(NUMBER_DATA, '+');
    ASTNode* negitiveExp = CreateASTNode(NUMBER_DATA, '-');

    ASTNodeAddChild(parentNode, positiveWhole);
    ASTNodeAddChild(parentNode, negitiveWhole);

    ASTNode* exponente = CreateASTNode(NUMBER_DATA, 'e');
    ASTNode* exponentE = CreateASTNode(NUMBER_DATA, 'E');

    ASTNodeAddChild(exponente, positiveExp);
    ASTNodeAddChild(exponente, negitiveExp);

    ASTNodeAddChild(exponentE, positiveExp);
    ASTNodeAddChild(exponentE, negitiveExp);

    //add numeric values
    //whole
    for(int i = 0; i < 10; i++){ 
         ASTNode* node = CreateASTNode(NUMBER_DATA, '0'+i);
         ASTNodeAddChild(parentNode, node);
        
         // these are nodes that can follow numeric nodes
         for(int j = 0; j < childCount; j++)
            ASTNodeAddChild(node, childNodes[j]);

        ASTListNode* listNode = CreateASTListNode(node);
        ASTListAppendNode(&wholeNumberNumericNodes, listNode);
    }

    //decimal
    for(int i = 0; i < 10; i++){ 
        ASTNode* node = CreateASTNode(NUMBER_DATA, '0'+i);

        for(int j = 0; j < childCount; j++)
            ASTNodeAddChild(node, childNodes[j]);

        ASTListNode* listNode = CreateASTListNode(node);
        ASTListAppendNode(&decimalNumberNumericNodes, listNode);
    }

    //exponent
    for(int i = 0; i < 10; i++){ 
        ASTNode* node = CreateASTNode(NUMBER_DATA, '0'+i);

        for(int j = 0; j < childCount; j++)
            ASTNodeAddChild(node, childNodes[j]);

        ASTListNode* listNode = CreateASTListNode(node);
        ASTListAppendNode(&exponentNumberNumericNodes, listNode);
    }
    
    //attach nodes to eachother
    //whole (each node can be the start of the number, therefor it is added to the parent node)
    ASTListNode* currentNode = wholeNumberNumericNodes;
    while(currentNode != NULL){ 
        ASTListNode* currentNodeInner = wholeNumberNumericNodes;
        while(currentNodeInner != NULL){
            ASTNodeAddChild(currentNode->node, currentNodeInner->node);
            currentNodeInner = currentNodeInner->next; 
        }

        currentNode = currentNode->next;
    }

    //decimal 
    currentNode = decimalNumberNumericNodes;
    while(currentNode != NULL){
        ASTListNode* currentNodeInner = decimalNumberNumericNodes;
        while(currentNodeInner != NULL){
            ASTNodeAddChild(currentNode->node, currentNodeInner->node);
            currentNodeInner = currentNodeInner->next; 
        }

        currentNode = currentNode->next;
    }

    //exponent
    currentNode = exponentNumberNumericNodes;
    while(currentNode != NULL){
        ASTListNode* currentNodeInner = exponentNumberNumericNodes;
        while(currentNodeInner != NULL){
            ASTNodeAddChild(currentNode->node, currentNodeInner->node);
            currentNodeInner = currentNodeInner->next; 
        }

        currentNode = currentNode->next;
    }
   
    //Add positive and negitive to whole numbers
    currentNode = wholeNumberNumericNodes;
    while(currentNode){
        ASTNodeAddChild(negitiveWhole, currentNode->node);
        ASTNodeAddChild(positiveWhole, currentNode->node);
        currentNode = currentNode->next;
    }

    //Add positive and negitive to whole numbers
    currentNode = exponentNumberNumericNodes;
    while(currentNode){
        ASTNodeAddChild(negitiveExp, currentNode->node);
        ASTNodeAddChild(positiveExp, currentNode->node);
        currentNode = currentNode->next;
    }

    //add decimal node after whole nodes
    currentNode = wholeNumberNumericNodes;
    while(currentNode != NULL){ 
        ASTNodeAddChild(currentNode->node, decimalPoint);
        currentNode = currentNode->next;
    }

    //add exponent nodes after whole nodes
    currentNode = wholeNumberNumericNodes;
    while(currentNode != NULL){ 
        ASTNodeAddChild(currentNode->node, exponente);
        ASTNodeAddChild(currentNode->node, exponentE);
        currentNode = currentNode->next;
    }

    //add exponent nodes after decimal nodes
    currentNode = decimalNumberNumericNodes;
    while(currentNode != NULL){ 
        ASTNodeAddChild(currentNode->node, exponente);
        ASTNodeAddChild(currentNode->node, exponentE);
        currentNode = currentNode->next;
    }
    
    //add decimal node before decimal nodes
    currentNode = decimalNumberNumericNodes;
    while(currentNode != NULL){
        ASTNodeAddChild(decimalPoint, currentNode->node);
        currentNode = currentNode->next;
    }

    //add E e node before exponent nodes
    currentNode = exponentNumberNumericNodes;
    while(currentNode != NULL){
        ASTNodeAddChild(exponente, currentNode->node);
        ASTNodeAddChild(exponentE, currentNode->node);
        currentNode = currentNode->next;
    }

    //add negitive postitve before whole numbers
    currentNode = wholeNumberNumericNodes;
    while(currentNode){
        ASTNodeAddChild(negitiveWhole, currentNode->node);
        ASTNodeAddChild(positiveWhole, currentNode->node);
        currentNode = currentNode->next;
    }

    DeleteASTList(&exponentNumberNumericNodes);
    DeleteASTList(&decimalNumberNumericNodes);
    DeleteASTList(&wholeNumberNumericNodes);  
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

void AddNullValues(ASTNode* parentNode, ASTNode** childNodes, int childCount){
    //null
    ASTNode* N = CreateASTNode(TEXT_DATA, 'n');
    ASTNode* U = CreateASTNode(TEXT_DATA, 'u');
    ASTNode* L1 = CreateASTNode(TEXT_DATA, 'l');
    ASTNode* L2 = CreateASTNode(TEXT_DATA, 'l');

    //connect
    ASTNodeAddChild(parentNode, N);
    ASTNodeAddChild(N, U);
    ASTNodeAddChild(U, L1);
    ASTNodeAddChild(L1, L2);

    for(int i = 0; i < childCount; i++){ 
        ASTNodeAddChild(L2, childNodes[i]);
    }
}

void PushToken(Queue* queue, String* dataString, TokenType tokenType, TokenValueType valueType){
    Token* token = CreateToken(dataString->string, tokenType, valueType);
    Push(queue, token);

    ClearString(dataString);
}

bool DiscardToken(ASTNode* currentSyntaxNode){
    TokenType type = currentSyntaxNode->TokenType;

    return (type == QUOTE || type == PAIR);
}

void Tokenize(ASTNode* currentSyntaxNode, char currentChar, String* tokenString, Queue* queue, TokenizeType* tokenizeState, bool isNumberToken){
    bool push = ChangeTokenizingState(currentSyntaxNode, tokenizeState);

    if(push){
        //all data type tokens get 'type erased' to just DATA for the tree to understand
        //token get assigned a secondary token type with what type the value actually is
        //there is 100% a better way to do this, but its whatever it works
        DetermineTokenValueType(tokenString);
        TokenValueType valueType = DetermineTokenValueType(tokenString);
        PushToken(queue, tokenString, DATA, valueType); 

        //tokens should carry a type however so json value can tell the type its holding
    }

    if(!DiscardToken(currentSyntaxNode)){
        AppendChar(tokenString, currentChar);

        //these are tokens like {[,]} getting pushed. these tokens have token types 
        //that help the tree build itslef like OPEN_OBJECT, CLOSE_ARRAY etc
        if(*tokenizeState == PUSH){
            PushToken(queue, tokenString, currentSyntaxNode->TokenType, NO_VALUE); 
        }
    }
}

bool ChangeTokenizingState(ASTNode* currentSyntaxNode, TokenizeType* currentState){
    TokenType tokenType = currentSyntaxNode->TokenType;

    if(tokenType == TEXT_DATA || (tokenType == NUMBER_DATA && *currentState == PUSH)){
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

TokenValueType DetermineTokenValueType(const String *tokenString){
    //check null and bool types
    if(strcmp(tokenString->string, "null") == 0){
        return NULL_VALUE;
    }else if(strcmp(tokenString->string, "true") == 0 || strcmp(tokenString->string, "false") == 0){
        return BOOL_VALUE;
    }

    //check int and float types
    char* endptr = NULL;
    strtol(tokenString->string, &endptr, 10);
    if(*endptr == '\0')
        return INT_VALUE;

    strtod(tokenString->string, &endptr);
    if(*endptr == '\0')
        return FLOAT_VALUE;

    return STRING_VALUE; 
}

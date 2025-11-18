#include "json/json.h"
#include "utils/ast.h"
#include "utils/file.h"
#include "utils/queue.h"
#include "utils/string.h"
#include "utils/token.h"
#include "json/jsonStack.h"

#include "json/jsonTokenBuilder.h"
#include "json/jsonTreeBuilder.h"
#include "json/jsonTree.h"

ASTTree* syntaxTree = NULL;
void JInit(){
    //Hey! this is straight up the worst code I think I may have ever written...
    //I Would do everything different If i had to write this again. But hey- it
    //works. This is the JSON Abstract Syntax tree hard coded...

    syntaxTree = CreateASTTree();

    ASTNode* Root = CreateASTNode(INVALID, '\0');

    ASTNode* OpenBracket = CreateASTNode('{', '{');
    ASTNode* CloseBracket = CreateASTNode('}', '}');
    
    ASTNode* OpenQuoteKey = CreateASTNode('"', '"');
    ASTNode* ClosedQuoteKey = CreateASTNode('"', '"');

    ASTNode* OpenQuotePair = CreateASTNode('"', '"');
    ASTNode* ClosedQuotePair = CreateASTNode('"', '"');

    ASTNode* Colon = CreateASTNode(':', ':');
    ASTNode* Camma = CreateASTNode(',', ',');

    ASTNode* OpenArray = CreateASTNode('[', '[');
    ASTNode* CloseArray = CreateASTNode(']', ']');

    //Array Syntax
    ASTNode* ArrayOpenBracket = CreateASTNode('{', '{');
    ASTNode* ArrayCloseBracket = CreateASTNode('}', '}');

    ASTNode* ArrayColon = CreateASTNode(':', ':');

    ASTNode* ArrayDataCamma = CreateASTNode(',', ',');
    ASTNode* ArrayObjectCamma = CreateASTNode(',', ',');

    ASTNode* ArrayOpenQuoteKey = CreateASTNode('"', '"');
    ASTNode* ArrayClosedQuoteKey = CreateASTNode('"', '"');

    ASTNode* ArrayOpenQuotePair = CreateASTNode('"', '"');
    ASTNode* ArrayClosedQuotePair = CreateASTNode('"', '"');

    ASTNode* ArrayStringStart = CreateASTNode('"', '"');
    ASTNode* ArrayStringEnd = CreateASTNode('"', '"');

    ASTNode* EndOfFile = CreateASTNode('\0', '\0');

    syntaxTree->root = Root;

    //Root Tree
    ASTNodeAddChild(Root, OpenBracket);
    ASTNodeAddChild(Root, OpenArray);

    //Open Bracket
    ASTNodeAddChild(OpenBracket, CloseBracket);
    ASTNodeAddChild(OpenBracket, OpenQuoteKey);

    //Closed Bracket
    ASTNodeAddChild(CloseBracket, CloseBracket);
    ASTNodeAddChild(CloseBracket, Camma);
    ASTNodeAddChild(CloseBracket, EndOfFile);

    //Open Quote Key
    ASTNodeAddChild(OpenQuoteKey, ClosedQuoteKey);
    AddAsciiToNode(OpenQuoteKey, &ClosedQuoteKey, 1);

    //Open Quote Pair
    ASTNodeAddChild(OpenQuotePair, ClosedQuotePair);
    AddAsciiToNode(OpenQuotePair, &ClosedQuotePair, 1); 
     
    //Closed Quote Key
    ASTNodeAddChild(ClosedQuoteKey, Colon);  

    //Closed Quote Pair
    ASTNodeAddChild(ClosedQuotePair, CloseBracket);
    ASTNodeAddChild(ClosedQuotePair, Camma);

    //Colon
    ASTNodeAddChild(Colon, OpenQuotePair);
    ASTNodeAddChild(Colon, OpenBracket);
    ASTNodeAddChild(Colon, OpenArray);

    ASTNode* NumericDataChildrenNodes[] = {Camma, CloseBracket};
    AddNumericCharactersToNode(Colon, NumericDataChildrenNodes, 2);
    AddBooleanValues(Colon, NumericDataChildrenNodes, 2);

    //Camma
    ASTNodeAddChild(Camma, OpenQuoteKey);
    ASTNodeAddChild(Camma, OpenArray);

    //Open Array
    ASTNodeAddChild(OpenArray, ArrayOpenBracket);
    ASTNodeAddChild(OpenArray, ArrayStringStart);
    ASTNodeAddChild(OpenArray, OpenArray);

    ASTNode* NumericArrayChildrenNodes[] = {ArrayDataCamma, CloseArray};
    AddNumericCharactersToNode(OpenArray, NumericArrayChildrenNodes, 2);
    AddBooleanValues(OpenArray, NumericArrayChildrenNodes, 2);
    
    //Close Array
    ASTNodeAddChild(CloseArray, Camma);
    ASTNodeAddChild(CloseArray, CloseBracket);
    ASTNodeAddChild(CloseArray, CloseArray);

    //Array Open Bracket
    ASTNodeAddChild(ArrayOpenBracket, ArrayOpenQuoteKey);

    //Array Closed Bracket
    ASTNodeAddChild(ArrayCloseBracket, ArrayDataCamma);
    ASTNodeAddChild(ArrayCloseBracket, CloseArray);
    
    //Array Open Quote Key 
    ASTNodeAddChild(ArrayOpenQuoteKey, ArrayClosedQuoteKey);
    AddAsciiToNode(ArrayOpenQuoteKey, &ArrayClosedQuoteKey, 1);

    //Array Open Quote Pair 
    ASTNodeAddChild(ArrayOpenQuotePair, ArrayClosedQuotePair);
    AddAsciiToNode(ArrayOpenQuotePair, &ArrayClosedQuotePair, 1);

    //Array Closed Quote Key
    ASTNodeAddChild(ArrayClosedQuoteKey, ArrayColon);
    ASTNodeAddChild(ArrayClosedQuoteKey, CloseArray);

    //Array Closed Quote Pair
    ASTNodeAddChild(ArrayClosedQuotePair, ArrayObjectCamma);
    ASTNodeAddChild(ArrayClosedQuotePair, ArrayCloseBracket);

    //Array Colon
    ASTNodeAddChild(ArrayColon, ArrayOpenQuotePair); 

    ASTNode* NumericArrayDataChildrenNodes[] = {ArrayObjectCamma, ArrayCloseBracket};
    AddNumericCharactersToNode(ArrayColon, NumericArrayDataChildrenNodes, 2);
    AddBooleanValues(ArrayColon, NumericArrayDataChildrenNodes, 2);

    //Array Camma
    ASTNodeAddChild(ArrayObjectCamma, ArrayOpenQuoteKey);

    //Array String Start
    ASTNodeAddChild(ArrayStringStart, ArrayStringEnd); 
    AddAsciiToNode(ArrayStringStart, &ArrayStringEnd, 1);

    //Array String End
    ASTNodeAddChild(ArrayStringEnd, ArrayDataCamma);
    ASTNodeAddChild(ArrayStringEnd, CloseArray);

    //Array Data Comma
    ASTNodeAddChild(ArrayDataCamma, ArrayOpenBracket);
    ASTNodeAddChild(ArrayDataCamma, ArrayStringStart);
    ASTNodeAddChild(ArrayDataCamma, OpenArray);

    AddNumericCharactersToNode(ArrayDataCamma, NumericArrayChildrenNodes, 2);
    AddBooleanValues(ArrayDataCamma, NumericArrayChildrenNodes, 2);
}

Json* JParse(const char* filePath){
    Json* tree = NULL;
    String* normalizedFile = GetNormalizedFile(filePath);

    Queue* queue = CreateQueue();
    bool succsess = JFileTokenize(normalizedFile, queue);

    if(succsess)
        tree = JCreateTree(queue);

    FreeQueue(&queue);
    DeleteString(&normalizedFile);

    return tree; 
}

bool JFileTokenize(String* normalizedFile, Queue* tokenQueue){
    ASTNode* currentSyntaxNode = syntaxTree->root; 

    unsigned int index = 0;     
    unsigned int scope = 0;

    String* currentTokenData = CreateString();
    TokenizeType tokenizeState = PUSH;
    
    while(true){
        char c = GetCharacter(normalizedFile, index);
        if(c == '\0')
            break;
        
        bool validToken = ValidateToken(&currentSyntaxNode, c);
        if(!validToken){
            printf("\nSyntax Error, Unexped Token %c at %d after %c. \n",
                c, index+1, currentSyntaxNode->AsciiValue);

            return false;
        } else { 
            Tokenize(currentSyntaxNode, c, currentTokenData, tokenQueue, &tokenizeState);
        }

        UpdateScope(currentSyntaxNode, &scope);
        index++;
    }

    if(scope != 0){
        perror("Syntax Error, Expected End of Data Not Found... Missing } or }?\n");
        return false;
    }

    return true;
}

Json* JCreateTree(Queue* tokenQueue){
    Json* root = NewJson(); 
    JsonStack* stack = NewJsonStack();

    Json* currentJsonNode = root;
    JsonTreeType treeType = T_OBJECT;

    int arrayIndex = 0;

    while(!IsQueueEmpty(tokenQueue)){
        Token* token = Pop(tokenQueue);
        TokenType tokenType = token->tokenType;

        JTreeBuildState treeState = GetTreeState(token);
        Json* newNode = NULL;

        switch(treeState){
            case SCOPE_IN:  
                ScopeJTreeIn(token, &currentJsonNode, stack, &treeType, &arrayIndex);
                break;

            case SCOPE_OUT:
                ScopeJTreeOut(stack, &treeType, &arrayIndex);
                break;

            case INLINE_NEW:
                AddChildNode(VALUE, stack, &currentJsonNode, treeType, &arrayIndex);
                break;

            case DATA_FILL:
                FillJsonData(token, currentJsonNode, treeType);
                break;

            case UNDEFINED:
                printf("Invalid Token %c, Cannot finish parsing\n", token->tokenType);
                break;
        }  

        if(token)
            FreeToken(&token);
    }

    DeleteJsonStack(&stack);
    
    return root;
}

void JDelete(Json** json){
    DeleteJson(json);
}

Json* JGetValue(Json* root, const char* key, JsonValue** value){
    if(root == NULL){
        return NULL;
    }

    int length = root->childLength;

    for(int i = 0; i < length; i++){
        Json* child = root->children[i];

        if(SameStringValue(child->key, key)){
            if(child->data == NULL){
                if(value)
                    *value = NULL;
                return child;
            }
            else{
                if(value){
                    *value = child->data; 
                    return NULL;
                }
            }
        }
    }

    return NULL;
}

void JEnd(){ 
    DeleteASTTree(&syntaxTree);
}

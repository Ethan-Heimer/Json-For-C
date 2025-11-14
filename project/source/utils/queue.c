#include "utils/queue.h"
#include "utils/token.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Queue* CreateQueue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void Push(Queue* queue, Token* token){
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->next = NULL;
    node->token = token;
    
    if(queue->front == NULL)
        queue->front = node;
    else
        queue->rear->next = node;
    
    queue->rear = node;
}


Token* Pop(Queue* queue){
    if(IsQueueEmpty(queue))
        return NULL; 

    QueueNode* node = queue->front;
    queue->front = queue->front->next;
    Token* token = node->token;

    free(node);

    return token;
}

bool IsQueueEmpty(Queue* queue){
    return queue->front == NULL;
}

void FlushQueue(Queue* queue){
    while(!IsQueueEmpty(queue)){
        Token* token = Pop(queue);
        FreeToken(&token);
    }
}

void FreeQueue(Queue** queue){
    if(*queue == NULL)
        return;

    FlushQueue(*queue);
    free(*queue);

    *queue = NULL;
}

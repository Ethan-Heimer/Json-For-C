#ifndef QUEUE_H
#define QUEUE_H

#include "utils/token.h"
#include <stdbool.h>

typedef struct QueueNode{
    Token* token;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue{
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* CreateQueue();

void Push(Queue*, Token* token);

Token* Pop(Queue*);

bool IsQueueEmpty(Queue*);

void FlushQueue(Queue*);

void FreeQueue(Queue**);

#endif

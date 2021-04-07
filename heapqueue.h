//
// Created by yorumum on 1/05/20.
//
#include <stdbool.h>

#ifndef CS380C_HEAPQUEUE_H
#define CS380C_HEAPQUEUE_H

typedef struct {
    int priority;
    int key;
} HeapQueue_entry;

typedef struct HeapQueue {
    HeapQueue_entry *array;
    unsigned int size;
    unsigned int max_size;
} HeapQueue;

int HeapQueue__cmp_entry(HeapQueue_entry a, HeapQueue_entry b);

bool HeapQueue__swap(HeapQueue *self, unsigned int parent_index, unsigned int child_index);

void HeapQueue__heapify_down(HeapQueue *self, unsigned int i);

void HeapQueue__heapify_up(HeapQueue *self, unsigned int i);

HeapQueue_entry HeapQueue__delete(HeapQueue *self, unsigned int i);

HeapQueue_entry HeapQueue_pop(HeapQueue *self);

bool HeapQueue_push(HeapQueue *self, int priority, int key);

HeapQueue *HeapQueue_init(int size);

void HeapQueue_free(HeapQueue *self);

#endif //CS380C_HEAPQUEUE_H


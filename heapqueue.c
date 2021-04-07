#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "heapqueue.h"


int HeapQueue__cmp_entry(HeapQueue_entry a, HeapQueue_entry b) {
    if (a.priority > b.priority || (a.priority == b.priority && a.key > b.key)) {
        return 1;
    }
    if (a.priority == b.priority && a.key == b.key) {
        return 0;
    }
    return -1;
}


bool HeapQueue__swap(HeapQueue *self, unsigned int parent_index, unsigned int child_index) {
    HeapQueue_entry parent = self->array[parent_index];
    HeapQueue_entry child = self->array[child_index];
    if (HeapQueue__cmp_entry(parent, child) == 1) {
        self->array[parent_index] = child;
        self->array[child_index] = parent;
        return true;
    }
    return false;
}

void HeapQueue__heapify_down(HeapQueue *self, unsigned int i) {
    while (2 * i + 1 < self->size) {
        unsigned int left_child_i = 2 * i + 1;
        unsigned int right_child_i = 2 * i + 2;
        unsigned int big_child_i = left_child_i;
        if (right_child_i < self->size &&
            HeapQueue__cmp_entry(self->array[left_child_i], self->array[right_child_i]) >= 0) {
            big_child_i = right_child_i;
        }
        if (!HeapQueue__swap(self, i, big_child_i)) {
            return;
        }
        i = big_child_i;
    }
}

void HeapQueue__heapify_up(HeapQueue *self, unsigned int i) {
    while (i > 0) {
        unsigned int parent_index = (i - 1) >> 1u;
        if (!HeapQueue__swap(self, parent_index, i)) {
            return;
        }
        i = parent_index;
    }
}

HeapQueue_entry HeapQueue__delete(HeapQueue *self, unsigned int i) {
    HeapQueue_entry deleted = self->array[i];
    HeapQueue_entry old_leaf = self->array[self->size - 1];
    self->array[i] = old_leaf;

    self->size -= 1;
    if (HeapQueue__cmp_entry(deleted, old_leaf) == 1 && i < self->size) {
        HeapQueue__heapify_up(self, i);
    } else {
        HeapQueue__heapify_down(self, i);
    }
    return deleted;
}

HeapQueue_entry HeapQueue_pop(HeapQueue *self) {
    return HeapQueue__delete(self, 0);
}

bool HeapQueue_push(HeapQueue *self, int priority, int key) {
    if (self->size == self->max_size) {
        return false;
    }
    HeapQueue_entry new_entry = {priority, key};
    self->array[self->size] = new_entry;
    self->size += 1;
    HeapQueue__heapify_up(self, self->size - 1);

    return true;
}


HeapQueue *HeapQueue_init(int size) {
    HeapQueue *instantiation = (HeapQueue *) malloc(sizeof(HeapQueue));
    instantiation->array = malloc(size * sizeof(HeapQueue_entry));
    instantiation->size = 0;
    instantiation->max_size = size;
    return instantiation;
}

void HeapQueue_free(HeapQueue *self) {
    free(self->array);
    free(self);
}

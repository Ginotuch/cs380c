#include <stdio.h>
#include <time.h>
#include "heapqueue.h"


int main() {
    clock_t t;
    t = clock();
    int dick_size = 10000000;
    HeapQueue *heap = HeapQueue_init(dick_size);
    for (int i = dick_size; i >= 0; i--){
        HeapQueue_push(heap, i, i);
    }
    while (heap->size != 0){
        HeapQueue_pop(heap);
    }
    HeapQueue_free(heap);
    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
    printf("%f", time_taken);
    return 0;
}
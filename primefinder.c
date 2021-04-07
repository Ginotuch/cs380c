#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int element_count;
    int max_size;
    int *array;
} IntList;

IntList *IntList_init() {
    IntList *a = (IntList *) malloc(sizeof(IntList));
    a->element_count = 0;
    a->max_size = 1;
    a->array = malloc(1 * sizeof(int));

    return a;
}

void IntList_push(IntList *a, int data) {
    if (a->element_count >= a->max_size) {
        int halfup = (a->max_size / 2) + (a->max_size % 2);
        if (halfup < 1) {
            halfup = 1;
        }
        int new_max = a->max_size + halfup;
        a->array = realloc(a->array, new_max * sizeof(int));
        a->max_size = new_max;
    }
    a->array[a->element_count++] = data;
}

void IntList_free(IntList *list) {
    free(list->array);
    free(list);
}

IntList *get_primes_fast_as_fuck(int x) {
    IntList *lits_o_primes = IntList_init();
    if (2 <= (x / 2)) {  //for some reason is a shit ton faster than (2 < x)
        IntList_push(lits_o_primes, 2);
    }

    for (int num = 3; num <= x; num = num + 2) {
        bool prime = true;

        //checks if divisible by previously found prime numbers, since everything has a prime factorisation
        for (int p_index = 0; prime && (p_index < lits_o_primes->element_count) &&
                              (lits_o_primes->array[p_index] <= (num / lits_o_primes->array[p_index]) + 1); p_index++) {
            if (num % lits_o_primes->array[p_index] == 0) {
                prime = false;
            }
        }
        if (prime) {
            IntList_push(lits_o_primes, num);
        }
    }
    return lits_o_primes;
}

IntList *f_finder(int f_x, IntList *prime_list) {  // returns prime factorisation
    int ind = 0;
    IntList *factors = IntList_init();
    while (f_x > 1) {
        if (f_x % prime_list->array[ind] != 0) {
            ind += 1;
        } else {
            IntList_push(factors, prime_list->array[ind]);
            f_x = f_x / prime_list->array[ind];
            ind = 0;
        }
    }
    return factors;
}

int main() {
    printf("Finding all primes less than 10,000,000:\n");

    int f_x = 10000000;

    clock_t t;
    t = clock();
    IntList *list_o_primes = get_primes_fast_as_fuck(f_x);
    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
    printf("  found %d primes\n  took %f seconds\n array space allocated %d\n", list_o_primes->element_count,
           time_taken, list_o_primes->max_size);

    IntList *factors = f_finder(f_x, list_o_primes);
    printf("Prime factorisation of %d: [", f_x);

    for (int i = 0; i < factors->element_count; i++) {

        printf("%d", factors->array[i]);

        if (i < factors->element_count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    IntList_free(list_o_primes);
    IntList_free(factors);
}

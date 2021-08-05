#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
    int *freqs;
    int *stats;
    hashing_t method;
};

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %11.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current    Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries    At Home   Collisions   Collisions\n");
    fprintf(stream, "------------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "------------------------------------------------------\n\n");
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word+++31 * result);
    }
    return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

htable htable_new(int capacity) {
    int i;
    htable hash_table = emalloc(sizeof *hash_table);

    hash_table->capacity = capacity;
    hash_table->num_keys = 0;
    hash_table->keys = emalloc(hash_table->capacity * sizeof hash_table->keys[0]);
    hash_table->freqs = emalloc(hash_table->capacity * sizeof hash_table->freqs[0]);

    for (i = 0; i < hash_table->capacity; i++) {
        hash_table->keys[i] = NULL;
    }

    for (i = 0; i < hash_table->capacity; i++) {
        hash_table->freqs[i] = 0;
    }
    
    return hash_table;
}

void htable_free(htable h) {
    free(h->keys);
    free(h->freqs);
    free(h);
}

int htable_insert(htable h, char *key) {
    int i;
    unsigned int index = htable_word_to_int(key);
    int remainder = htable_hash(h, index);

    if (h->keys[remainder] == NULL) {
        h->num_keys++;
        printf("NULL\n");
        return 1;
    }
    if (h->keys[remainder] != NULL && strcmp(key, h->keys[remainder]) != 0) {
        for (i = 0; i <= h->capacity; i++) {
            if (h->keys[remainder] != NULL && h->capacity == i) {
                i = 0;
            }
            if (h->keys[remainder] != NULL && h->capacity == i) {
                printf("Not null\n");
                h->num_keys++;
            }
            if (strcmp(key, h->keys[remainder]) == 0) {
                h->keys[remainder] = key;
            }
        }
    } else {
        return 1;
    }

    return 0;
}

void htable_print(htable h) {
    int i;

    for (i = 0; i < h->capacity; i++) {
        if (h->keys[i] != NULL) {
            printf("%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
        }
    }
}

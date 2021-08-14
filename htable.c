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

htable htable_new(int capacity) {
    int i;
    htable h = emalloc(sizeof *h);
    h->capacity = capacity;
    h->num_keys = 0;
    h->freqs = emalloc(capacity * sizeof h->freqs[0]);
    h->keys = emalloc(capacity * sizeof h->keys[0]);
    
    for (i = 0; i < capacity; i++) {
        h->freqs[i] = 0;
        h->keys[i] = NULL;
    }
    
    return h;
}

void htable_free(htable h) {
    free(h->keys);
    free(h->freqs);
    free(h);
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *str, int do_double_hashing) { /* this is to let all know that my double hashing method will soon be incorperated
into this method so that both can work in the same method block of code*/
    unsigned int str_int;
    unsigned int index;
    unsigned int original;
        
    str_int = htable_word_to_int(str);
    index = str_int % h->capacity;
    original = index; 

    if (h->keys[index] == NULL) {
        h->keys[index] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
        strcpy(h->keys[index], str);
        h->freqs[index] = 1;
        h->num_keys++;

        return 1;
    } else if (strcmp(h->keys[index], str) == 0) {
        h->freqs[index]++;
        
        return h->freqs[index];
    }
    
    while (h->keys[index] != NULL && strcmp(h->keys[index], str) != 0) {
        index = (index + 1) % h->capacity;
        if (index == original) {
            return 0;
        }

        if (h->keys[index] == NULL) {
            h->keys[index] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
            strcpy(h->keys[index], str);
            h->freqs[index] = 1;
            h->num_keys++;

            return 1;
        } else if (strcmp(h->keys[index], str) == 0) {
            h->freqs[index]++;

            return h->freqs[index];
        }
    }
    
    return 0;
}


void htable_print(htable h, FILE *stream) {
    int i;

    for (i = 0; i < h->capacity; i++) {
        if (h->keys[i] != NULL) {
            fprintf(stream, "%d %s\n", h->freqs[i], h->keys[i]);
        }
    }
}

void htable_print_entire_table(htable h, FILE *stream) {
    int i;
    fprintf(stream, "Pos Freq Stats Word\n");
    fprintf(stream, "---------------------------\n");
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "\%5d \%5d \5d   \%s\n", i, h->freqs[i], h->stats[i], h->keys[i]);
    }
}


/* Double hashing Method V1 */

static unsigned int htable_double_hash(htable table, unsigned int i_key){
    return 1 + i_key * (second_hash(i_key))%(table->capacity - 1);
}

static unsigned int second_hash(htable table, unsigned int i_key){
    return (i_key % (table->capacity - 1));
}

static int prime_round(int input)
{
    int i;
    if (input <= 1)
    {
        input = 2;
    }
    for (;; input++)
    {
        i = 2;
        while (i < input)
        {
            if (input % i == 0)
            {
                break;
                /* this i value needs to be the new capacity value for a hash table in 
         the new_table() method call. And has to be use throughout the remaining methods*/
            }
            i++;
        }
        if(i == input){
            return input;

        }
    }




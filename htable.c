/****************************************************************************
 * @file htable.c 
 * @author Connor Dobson    Student_ID: 
 * @author Hayden Knox      Student_ID: 2485875
 * 
 * The purpose of this program is to respond to user inputs reading both a 
 * specified text file and single letter characters entered by users.
 * These characters dictate what functions are to be executed and perforemed 
 * on the input text files.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

/****************************************************************************
 * This struct is used to create a composite datatype declaration which 
 * defines a group of listed variables under one variable type in a block of 
 * computer memory. Each variable can be altered by use of a single pointer
 * 
 * Variables:
 * @param capacity: 
 * This variable defines the maximum size of a hash table which is a prime 
 * number for more efficient hash table creation.
 * @param num_keys: 
 * This variable defines the number of words which have been inserted into 
 * the hash table. 
 * @param keys: 
 * This variable represents the key value for an individual word which has 
 * been inserted into a hash table.
 * @param freqs:
 * This variable represents the number of times which an individual word 
 * occurs in a hash table and is determined by the number of insertion 
 * function attempts.
 * @param stats:
 * This variable is used to store the various number of statistics for hash
 * tables including, freqs, keys and num_keys
 * @param method:    
 * Is used to indicate what form of hashing method is to be used to store hash
 * table entries, and dictate if the double or linear hashing method is used.
 ***************************************************************************/
struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
    int *freqs;
    int *stats;
    hashing_t method;
};

/****************************************************************************
 * Function:
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 ***************************************************************************/
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

/****************************************************************************
 * Function:
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
 ***************************************************************************/
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
/****************************************************************************
 * Function:
 * This static method is used to hash words into specific indexes, once a index
 * is occupied by a a hashed word this method moces the indexing insertion location
 * to a new indexed location in order to find a new available index. 
 * 
 * @param htable h: 
 * This variable represents the current instance of a hash table being processed 
 * @param i_key:
 * This variable is the index of a word whick has been keyed into the hash table.
 * @return the new index of a hash table key value.
 ***************************************************************************/
static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

/****************************************************************************
 * Function:
 * This method is used to create a new instance of a hash table and allocating 
 * the memory required to create a new hash table instance. IN addition this 
 * method also determines if a nerw hash table being created will employ the
 * use of double hashing or linear hashing.
 * 
 * @param capacity:
 * This variable defines the maximum number of possible indexes for a hash table.
 * Every key value (word input) which is read will be allocated to a specific
 * index which is withing the limit of the htable capacity
 * @param: enable_double
 * This variable which acts as a boolean flag described on the file asgn1.c
 * is used to determine from the users command line input if they wish to perform 
 * double hashing instead of linear hashing.
****************************************************************************/
htable htable_new(int capacity, int enable_double) {
    int i;
    htable h = emalloc(sizeof *h);
    h->capacity = capacity;
    h->num_keys = 0;
    h->freqs = emalloc(capacity * sizeof h->freqs[0]);
    h->keys = emalloc(capacity * sizeof h->keys[0]);
    h->stats = emalloc(capacity * sizeof h->stats[0]);

    if (enable_double == 1) {
        h->method = DOUBLE_H;
    } else {
        h->method = LINEAR_P;
    }
    
    for (i = 0; i < capacity; i++) {
        h->freqs[i] = 0;
        h->keys[i] = NULL;
    }
    
    return h;
}

void htable_free(htable h) {
    free(h->keys);
    free(h->freqs);
    free(h->stats);
    free(h);
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *str) {
    unsigned int str_int;
    unsigned int index;
    unsigned int original;
    unsigned int step;
    int attempt = 0;
    str_int = htable_word_to_int(str);
    if (h->method == DOUBLE_H) {
        step = htable_step(h, str_int);
    }
    index = str_int % h->capacity;
    original = index; 
    
    if (h->keys[index] == NULL) {
        h->keys[index] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
        strcpy(h->keys[index], str);
        h->freqs[index] = 1;
        h->stats[h->num_keys] = attempt;
        h->num_keys++;
        return 1;
    } else if (strcmp(h->keys[index], str) == 0) {
        h->freqs[index]++;
        return h->freqs[index];
    }
    
    while (h->keys[index] != NULL && strcmp(h->keys[index], str) != 0) {
        if (h->method == DOUBLE_H) {
            index = (index + step) % h->capacity;
        } else {
            index = (index + 1) % h->capacity;
        }
        if (index == original) {
            return 0;
        }

        attempt++;
            
        if (h->keys[index] == NULL) {
            h->keys[index] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
            strcpy(h->keys[index], str);
            h->freqs[index] = 1;
            h->stats[h->num_keys] = attempt;
            h->num_keys++;
            return 1;
        } else if (strcmp(h->keys[index], str) == 0) {
            h->freqs[index]++;
            return h->freqs[index];
        }
    }
    return 0;
}


void htable_print(htable h, FILE *stream, void print_function(int freq, char *word)) {
    int i;

    for (i = 0; i < h->capacity; i++) {
        if (h->keys[i] != NULL) {
            print_function(h->freqs[i], h->keys[i]);
        }
    }
}

void htable_print_entire_table(htable h, FILE *stream) {
    int i;
    fprintf(stream, "%5s  %5s  %5s  %5s\n", "Pos", "Freq", "Stats", "Word");
    fprintf(stream, "---------------------------\n");
    for (i = 0; i < h->capacity; i++) {
        if (h->keys[i] == NULL) {
            fprintf(stream, "%5d %5d %5d\n", i, h->freqs[i], h->stats[i]);
        } else {
            fprintf(stream, "%5d %5d %5d   %s\n", i, h->freqs[i], h->stats[i], h->keys[i]);
        }
    }
}



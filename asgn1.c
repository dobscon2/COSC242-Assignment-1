#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "htable.h"
#include "mylib.h"

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char* argv[]) {
    htable table = htable_new(113);
    char word[80];

    while (getword(word, sizeof word, stdin) != EOF) {
        fprintf(stdout, "inserting %s\n", word);
        htable_insert(table, word);
    }

    htable_print(table, stdout);
    htable_free(table);
    const char *optstring = "d:e:p:s:t:h";
    char option;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'd':
                /* double hashing option */
                break;
            case 'e':
                /* display contents of hash table */
                break;
            case 'p':
                /* print stats */
                break;
            case 's':
                /* snapshot of table */
                break;
            case 't':
                /* tablesize */
                break;
            case 'h':
                fprintf(stderr, "Usage: %s [OPTION]... <STDIN>\n", argv[0]);
                fprintf(stderr, "\n");
                fprintf(stderr, "Perform various operations using a hash table. By default, words are\nread from stdin and adding to the hash table, before being printed out\nalongside their frequencies to stdout.\n\n");
                fprintf(stderr, "-d\t\tUse double hashing (linear probing is the default)\n");
                fprintf(stderr, "-e\t\tDisplay entire contents of hash table on stderr\n");
                fprintf(stderr, "-p\t\tPrint stats info instead of frequencies & words\n");
                fprintf(stderr, "-s SNAPSHOTS\tShow SNAPSHOTS stats snapshots (if -p is used)\n");
                fprintf(stderr, "-t TABLESIZE\tUse the first prime >= TABLESIZE as htable size\n");
                fprintf(stderr, "\n");
                fprintf(stderr, "-h\t\tDisplay this message\n\n");
                return EXIT_FAILURE;
                break;
            default:
                fprintf(stderr, "Usage: %s [OPTION]... <STDIN>\n", argv[0]);
                fprintf(stderr, "\n");
                fprintf(stderr, "Perform various operations using a hash table. By default, words are\nread from stdin and adding to the hash table, before being printed out\nalongside their frequencies to stdout.\n\n");
                fprintf(stderr, "-d\t\tUse double hashing (linear probing is the default)\n");
                fprintf(stderr, "-e\t\tDisplay entire contents of hash table on stderr\n");
                fprintf(stderr, "-p\t\tPrint stats info instead of frequencies & words\n");
                fprintf(stderr, "-s SNAPSHOTS\tShow SNAPSHOTS stats snapshots (if -p is used)\n");
                fprintf(stderr, "-t TABLESIZE\tUse the first prime >= TABLESIZE as htable size\n");
                fprintf(stderr, "\n");
                fprintf(stderr, "-h\t\tDisplay this message\n\n");
                return EXIT_FAILURE;
                break;
        }
    }

/*
    int enable_double = 0;
    if(enable_double == 1){
        enable_double = htable_new(table);
    }
*/
    return EXIT_SUCCESS;
}

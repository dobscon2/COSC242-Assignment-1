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
                /* htable_double_hash(htable table, unsigned int i_key){      - Hayden 14/08/2021*/
                break;
            case 'e':
                /* display contents of hash table */
                /* htable_print(htable h, FILE *stream)                       - Hayden 14/08/2021*/
                break;
            case 'p':
                /* htable_print_stats(htable h, FILE *stream, int num_stats)  - Hayden 14/08/2021*/
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

/* prime number checker - Hayden Knox 13/08/2021*/

/*
int prime_round(int input){
 int i = input;
 while(i >= input) {
     i++;
     if(i % 1 == 0 && i % i == 1){
         printf("%d is a prime number?");
         return i;
         /* this i value needs to be the new capacity value for a hash table in 
         the new_table() method call. And has to be use throughout the remaining methods*/

         /* this wil have to be called in the main method. 
     } else {
         printf("%d is not a prime number?");
         return 0;
     }
    }
 }

int main(){
    int input;
    scanf("%d Enter an int", &input);
    prime_round(input);
    return 1;
}
*/
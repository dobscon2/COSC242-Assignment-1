#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "htable.h"
#include "mylib.h"

/* setting up a repository connection*/

int prime_round(int input)
{
    printf("this is working");
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
}


static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}
/*
Visual Studio might have changed it back to Powershell, when you start Visual Code back up switch the terminal to Ubuntu WSL
*/

int main(int argc, char* argv[]) {
    htable table;
    int h_size = 113;
    char word[80];
    const char *optstring = "dephs:t:";
    char option;
    int num_stats = 10;
    int do_double_hashing = 0;
    int do_htable_print = 0;
    int do_print_stats = 0;
    int do_print_snapshots = 0; 
    int do_enter_tablesize = 0;
        while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'd':
                /* this is do double hashing option */
                do_double_hashing = 1;
                /*- Hayden 14/08/2021*/
                break;
            case 'e':
                /* display contents of hash table */
                do_htable_print = 1;
                /*- Hayden 14/08/2021*/
                break;
            case 'p':
                /*htable_print_stats(htable h, FILE *stream, int num_stats)  - Hayden 14/08/2021*/
                do_print_stats = 1;
                /* print stats */
                break;
            case 's':
                /* snapshot of table */
                if(num_stats < 0){
                    fprintf(stderr, "The number to be entered must be greater than 0");
                    exit(1);
                }
                num_stats = atoi(optarg);

                break;
            case 't':
            h_size = prime_round(atoi(optarg));

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
                /* May not need  Hayden 14/08/2021*/
            default:
                break;
        }
    }
    table = htable_new(h_size, do_double_hashing);
    while (getword(word, sizeof word, stdin) != EOF) {
        fprintf(stdout, "inserting %s\n", word);
        htable_insert(table, word);
    }

    if (do_htable_print == 1){
        htable_print_entire_table(table, stderr); 
    }

    if (do_print_stats == 1) {
        htable_print_stats(table, stdout, num_stats);
    }

    if (do_print_stats != 1) {
        htable_print(table, stdout, print_info);
    }
    htable_free(table);

    return EXIT_SUCCESS;
}
/* The double hashing method is being included via the third parameter of the insert function.
i will be altering the insert function soon. The main method function is almost error free. - 14/08/21 */
/* prime number checker DONE- Hayden Knox 13/08/2021*/

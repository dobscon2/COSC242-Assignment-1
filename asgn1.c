#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "htable.h"
#include "mylib.h"

static void print_info(int freq, char *word) {
    printf("-4d %s\n", freq, word);
}

int main(int argc, char* argv[]) {
    const char *optstring = "d:e:p:s:t:h";
    char option;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'd':
                /* double hashing option */
            case 'e':
                /* display contents of hash table */
            case 'p':
                /* print stats */
            case 's':
                /* snapshot of table */
            case 't':
                /* tablesize */
            case 'h':
                /* display help message */
            default:
                /* display default message */
        }
    }
}

/****************************************************************************
 * @file asgn1.c 
 * @author Connor Dobson    Student_ID: 1043665
 * @author Hayden Knox      Student_ID: 2485875
 * 
 * The purpose of this program is to respond to user inputs reading both a 
 * specified text file and single letter characters entered by users.
 * These characters dictate what functions are to be executed and perforemed 
 * on the input text files.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "htable.h"
#include "mylib.h"

/****************************************************************************
 * Function: 
 * This method takes in an integer value and assesses if this value does or 
 * doesn't equal a prime number. Initially the method checks if the input 
 * variable is less than the value one by default. If so then the variable 
 * input is assignment the value of two for minimum hash table size. 
 * The itterator variable i incriments to check if the input variable is 
 * dvisible by a factor. This loop repeatedly executes infinitely 
 * incrementing the int input variable provided until either i is greater 
 * than or equal to input. This new value of the variable input is the 
 * nearest whole prime number to the user input specifying the size of a hash
 * table.
 * 
 * @param input: 
 * -> This method parameter is given by the prime_round(atoi(optarg)); method 
 * call. Reading input provided from the terminal command line this line 
 * converts the chracter input into and primative int value. The value 
 * returned by this method is stored in the variable h_size which is passed 
 * as a parameter in other asgn1.c functions
 * @return input: is the greater nearest whole prime number to the input 
 * paramter.
 ***************************************************************************/

int prime_round(int input)
{
    int i;
    if (input <= 1){
        input = 2; /* This line of code is used to specify the minimum 
                    * hash-table size for any hash-table size specification which is 
                    * less than or equal to the value of one.*/  
    }
    for (;; input++){ /* this loop incriments the value of input until it 
                       * reaches a value which is not divisible by the incriment divisor 
                       * variable i and greater than its original value. */
        i = 2;
        while (i < input){
            if (input % i == 0){ /* this boolean if statement evaluates the
                                  * input variable by dividing the variable input by i and 
                                  * dececting for each time both variables incriment if the input
                                  * variable is divisible by a common factor. */   
                break;

                /* The i value of variable i needs to determine new capacity
                 * value for the a hash table in the new_table() method call. */
            }
            i++;  /* this could be a for loop but a while loop seemed prudent 
                   * than adding a single for loop which was more absolute. */
        }
        if(i == input){  /* if the value of i variable is equal to the input 
                          * variable this proves that if the other previous checks havent
                          * executed and that the new input variable value is a prime number. */ 
            return input; /* this is the new prime number which is returned
                           * to specify the zise of a hash table. */  

        }
    }
}
/****************************************************************************
 * Function:
 * This static function prints out to the terminal the words which have been 
 * inserted into the hash table and the number of times identical words have
 * occoured and been inserted into the hash table. Adjacent to the word 
 * inserted is the frequency in which that word has occoured.
 * @param freq: Is the number of times a signle word has been inserted as
 * read from the input text file.
 * @param *word is the array or charatcers which has been read in as input 
 * from the while loop whjich is now stored in the hash table.
 ***************************************************************************/

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

/****************************************************************************
 * Function: 
 * This method takes in an integer value and assesses if this value does or 
 * doesn't equal a prime number. Initially the method checks if the input 
 * variable is less than the value one by default. If so then the variable 
 * input is assignment the value of two for minimum hash table size. 
 * The itterator variable i incriments to check if the input variable is 
 * dvisible by a factor. This loop repeatedly executes infinitely 
 * incrementing the int input variable provided until either i is greater 
 * than or equal to input. This new value of the variable input is the 
 * nearest whole prime number to the user input specifying the size of a hash
 * table.
 * 
 * @param input: 
 * -> This method parameter is given by the prime_round(atoi(optarg)); method 
 * call. Reading input provided from the terminal command line this line 
 * converts the chracter input into and primative int value. The value 
 * returned by this method is stored in the variable h_size which is passed 
 * as a parameter in other asgn1.c functions
 * @return input: is the greater nearest whole prime number to the input 
 * paramter.
 ***************************************************************************/

int main(int argc, char* argv[]) {
    htable table; /* this statment is used to create a new instance of a hash
                   * table, the new_htable() method is called and stored in this variable. */
    int h_size = 113;  /* If there is not provided hashtable size specified by
                        * a user input a default table size of 113 is provided for effective 
                        * hashing. */ 
    char word[80]; /* this variable specifies the maximum length words which
                    * can be read by the wile loop within the main methods initial execution. */
    const char *optstring = "dephs:t:";  /* this string of chars specifies the
                                          * ascii characters which can be accepted as input and perform function
                                          * executions based. each character corresponds to the case block of code
                                          * within the while loop. */
    char option;
    int num_stats = 10; /* this variable defines the default number of  
                         * percentile incriments printed by the print_stats() function. !! */

    /*
    * The following three variables are boolean flags which are used to invoke
    * method calls for various methods which corespond to thier matching 
    * variable titles, once thier value changes from 0 to 1. The matching
    * method is called in the following if statements. */

    int do_double_hashing = 0;
    int do_htable_print = 0;
    int do_print_stats = 0;

/****************************************************************************
 * This while loop continues to execute while the condition of reading in  
 * words/text ascii charcters until the condition != EOF (end of file) is 
 * evaluated as equal. This is compared to the variable option which uses
 * the getopt method to read in input of three command line entries. 
 */
        while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'd':
                /* This case charcter 'd' is used to detect if the user wishes 
                 * to perform double hashing processes on thier text input file. */ 
                do_double_hashing = 1;
                break;
            case 'e':
                /* This case charcter 'e' is used to detect if the user wishes
                 * to display the entire hash tasble content based on thier text 
                 * input file */ 
                do_htable_print = 1;
                break;
            case 'p':
                /* This case charcter 'p' is used to detect if the user wishes to 
                 * print out the statistic of hashing collisions, table occupancy
                 * percentage, successful hashing numbers and repreted word count */  
                do_print_stats = 1;
                break;
            case 's':
                /* This case charcter 's' is used to detect how many or the number
                 * of percential hash table incriments the user wants to display
                 * and thier corresponding statistics for each percential incriment */
                if(num_stats < 0){
                    fprintf(stderr, "The number to be entered must be greater than 0");
                    exit(1);
                }
                /* this statements assigns the value of the number of statistical
                 * incriments required by the user to the num_stats variable. the 
                 * atoi() method reads in the value of the the character entered 
                 * by the user in the command line an converts it into an integer. */
                num_stats = atoi(optarg);

                break;
            case 't':
                /* refer to method function for a descripotion of this statements
                 * purpose. */
                h_size = prime_round(atoi(optarg));
                break;
            case 'h':
                /* This character 'h' when entered by the user or by default will
                 * print out the possible characters and thier coresponding functions.
                 * Providing a concise definition as to what each function does.
                 * And specifiying the format of the parameters they each function
                 * accepts.
                 */
                
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
            default:
                /* This case will print out only when an invalid option is detected in the command line argument
                 * it will print out the invalid option and display the same help message to the user.
                 */
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
    table = htable_new(h_size, do_double_hashing);
    /* This while loop is responsible for the insertion of each word within 
     * an input text file. It executes until the end of the text file is 
     * reached this llop stops executing and for each loop execution each
     * for is inserted into the current hash table instance. */ 
    while (getword(word, sizeof word, stdin) != EOF) {
        fprintf(stdout, "inserting %s\n", word);
        htable_insert(table, word);
    }
    /* if the integer boolean flag value for the variable do_htable_print
     * changes from 0 to 1, which evaluates to true, the method 
     * htable_print_entire_table is called. */
    if (do_htable_print == 1){
        htable_print_entire_table(table, stderr); 
    }
    /* if the integer boolean flag value for the variable do_print_stats
     * changes from 0 to 1, which evaluates to true, the htable_print_stats()
     * method is called, this flag is used to indicate if the user prints
     * a specific number of percentile hashtable incriments. */
    if (do_print_stats == 1) {
        htable_print_stats(table, stdout, num_stats);
    }
    /* if the integer boolean flag value for the variable do_print_stats
     * doesn't change from 0. This if statement evaluates to true unlike
     * the previous if statement, the htable_print_stats()
     * method is called, this flag is used to indicate if the user prints
     * a specific number of percentile hashtable incriments. */
    if (do_print_stats != 1) {
        htable_print(table, print_info);
    }
    /* this statement after execution of all of the required functions frees
     * and deallocates all of the memory used in the creation of a hash table */ 
    htable_free(table);

    return EXIT_SUCCESS;
}

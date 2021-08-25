/****************************************************************************
 * @file htable.h 
 * @author Connor Dobson    Student_ID: 1043665
 * @author Hayden Knox      Student_ID: 2485875
 * 
 * The purpose of this program is to contain definitions of htable.c 
 * functions to be used in the main methods within the function asgn1.c.
 * These functions and thier associated variables need to be imported 
 * into the C program using the #include statement. 
 ***************************************************************************/

#ifndef HTABLE_H_
#define HTABLE_H_

typedef struct htablerec *htable;
typedef enum hashing_e { LINEAR_P, DOUBLE_H } hashing_t;

extern void htable_free(htable h);
extern int htable_insert(htable h, char *str);
extern htable htable_new(int capacity, int enable_double);
extern void htable_print(htable h, void print_function(int freq, char *word));
extern int htable_search(htable h, char *str);
extern void htable_print_stats(htable h, FILE *stream, int num_stats);
void htable_print_entire_table(htable h, FILE *stream);

#endif

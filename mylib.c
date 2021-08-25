/****************************************************************************
 * @file mylib.c 
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
#include "mylib.h"
#include <assert.h>
#include <ctype.h>

/****************************************************************************
 * Function:
 * This function allocates memory needed to store a variable of a greater size
 * 
 * @param s: 
 * This parameter represents the amount for memorey needed 
 * to hold the entire contents of a hash table.
 * @return result:
 * This return statement returns the new amount of memory required to store 
 * a hashtable
 ***************************************************************************/
void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
/****************************************************************************
 * Function: 
 * This function reallocates memory when the maximum amount of allocated memory
 * is met for a variable and allocates additional memory when more is required
 * 
 * @param s:
 * This parameter represents the amount for memorey needed 
 * to hold the entire contents of a hash table.
 * @return result:
 * This return statement returns the new amount of memory required to store 
 * a hashtable
 *****************************************************************************/
void *erealloc(void *p, size_t s){
    void *result = realloc(p, s);
    if(NULL == result){
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
/****************************************************************************
 * Function:
 * This function reads individual words seperated by whitespace characters.
 * The textfile input is read from the command line input stream. This
 * function reads in text words until the end of the file is reached.
 * 
 * @param char:
 * This parameter is the current charcter read which signifies the beginning 
 * of a string of charcters until white space is encountered.
 * @param limit:
 * 
 * @param stream:
 * Is the input from the file read in as text input from the command line to 
 * be processed into a hash table.
 ***************************************************************************/
int getword(char *s, int limit, FILE *stream){
    int c;
    char *w = s;
    assert(limit > 0 && s !=NULL && stream != NULL);

    /*skip to start of word*/
    while(!isalnum(c = getc(stream)) && EOF != c);

    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) {
        *w++ = tolower(c);
    }

    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w -s;
}

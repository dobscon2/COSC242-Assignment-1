/****************************************************************************
 * @file mylib.h 
 * @author Connor Dobson    Student_ID: 1043665
 * @author Hayden Knox      Student_ID: 2485875
 * 
 * The purpose of this program is to hold definitions of memory allocation 
 * functions and a input string reader function getword()to be used within 
 * the file htable.c. These functions and thier associated variables need 
 * to be imported into the C program using the #include statement. 
 ***************************************************************************/


#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern int getword(char *s, int limit, FILE *stream);

#endif

///
/// File:  classes.h
/// Description:  Defines names for character classes used in the
///               CSCI-243 transition matrix project.
///
/// @author Warren R. Carithers
///

#ifndef _CLASSES_H_
#define _CLASSES_H_

   // whitespace characters:  space, tab, newline
#define	CC_WS	   	0

   // alphabetic (A-Z, a-z) and underscore
#define	CC_ALPHA   	1

   // digit character 0
#define	CC_ZERO    	2

   // octal/decimal digit characters 1-7
#define	CC_OCTAL  	3

   // decimal digit characters 8, 9
#define	CC_DECIMAL 	4

   // division operator
#define	CC_SLASH	5

   // multiplicative operator
#define	CC_STAR 	6

   // other arithmetic operators: +, -, %
#define	CC_ARITH 	7

   // any other ASCII character
#define	CC_OTHER   	8

   // EOF on input
#define	CC_EOF  	9

   // any non-ASCII character
#define	CC_ERROR   	10

   // number of character classes
#define	NUM_CLASSES	11

#endif

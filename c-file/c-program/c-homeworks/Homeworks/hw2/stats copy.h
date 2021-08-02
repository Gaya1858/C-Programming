///
/// File: stats.h
/// stats.h is the interface for functions in a simple statistics module.
///
/// @author csci243: Mechanics Course Account
/// @author gk4045 Gayathri Kanagaraj
/// @date 08/28/2020
///
///

#ifndef STATS_H
#define STATS_H

///calaculate average score value
///@param count  size of the array
///@param scores int array with scores
///@return  double value of average of scores

double average( int count, const int scores[] );

////calaculate average score value
///@param count  size of the array
///@param scores int array with scores
///@param mean  double average value of the scores
///@return  double value of standard deviation  of scores

double std_dev( int count, const int scores[], double mean );

////Creates grade table
///@param count  size of the array
///@param scores int array with scores

void histogram( int count, const int scores[] );
                                                  
#endif // STATS_H


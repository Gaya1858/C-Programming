///
/// stats.c
///  description: implementation of stats functions
/// @author csci243: Mechanics Course Account
/// @author gk4045 Gayathri Kanagaraj
/// @date 08/28/2020

#include "stats.h"
#include <math.h>
#include <stdio.h>

///computes  average  or mean value of the array of scores
///@param count  size of the array
///@param scores int array with scores
///@return  double value of average of scores

double average( int count, const int scores[] ){
    
    double mean =0.0;
    double sum =0;
    for(int i =0; i<count;i++){
        sum+=scores[i];
    }
    mean = sum/count;
    return mean;
}

////computes  standard deviation value of the  scores in  the array
///@param count  size of the array
///@param scores int array with scores
///@param mean  double average value of the scores
///@return  double value of standard deviation  of scores

double std_dev( int count, const int scores[], double mean ){
    double deviation=0.0;
    double sum =0.0;
    for(int i =0; i<count;i++){
        sum+=((scores[i] - mean)*(scores[i] - mean));
    }
    deviation = sqrt(sum/(count-1));
    
    return deviation;
}
///histogram funtion prints out a table of grades options and no of grades in that that
///Creates grade table based on the scores 
///@param count  size of the array
///@param scores int array with scores

void histogram( int count, const int scores[] ){
    int alphabet[10]={0,0,0,0,0,0,0,0,0,0};
        for(int i =0; i< count; i++){
            if(scores[i]>=92){
                alphabet[0]=alphabet[0]+1;;
            }
            
            if(scores[i]>=89 &&scores[i]<92){
                
                alphabet[1]=alphabet[1]+1;;
            }
            
            if(scores[i]>=85 &&scores[i]<89){
                
                alphabet[2]=alphabet[2]+1;;
            }
            
            if(scores[i]>=82 &&scores[i]<85){
                
                alphabet[3]=alphabet[3]+1;;
            }
          
            if(scores[i]>=79 &&scores[i]<82){
                
                alphabet[4]=alphabet[4]+1;;
            }
            
            if(scores[i]>=75 &&scores[i]<79){
                
                alphabet[5]=alphabet[5]+1;;
            }
           
            if(scores[i]>=72 &&scores[i]<75){
                
                alphabet[6]=alphabet[6]+1;;
            }
            
            if(scores[i]>=69 &&scores[i]<72){
                
                alphabet[7]=alphabet[7]+1;;
            }
            
            if(scores[i]>=60 &&scores[i]<69){
                
                alphabet[8]=alphabet[8]+1;;
            }
            
            if(scores[i]<60){
                
                alphabet[9]=alphabet[9]+1;;
            }
        }
        for( int i =0; i<10; i++){
            if(i ==0){
                printf("A:\t%d\n",alphabet[i]);
            }
            if(i ==1){
                printf("A-:\t%d\n",alphabet[i]);
            }
            if(i ==2){
                printf("B+:\t%d\n",alphabet[i]);
            }
            if(i ==3){
                printf("B:\t%d\n",alphabet[i]);
            }
            if(i ==4){
                printf("B-:\t%d\n",alphabet[i]);
            }
            if(i ==5){
                printf("C+:\t%d\n",alphabet[i]);
            }
            if(i ==6){
                printf("C:\t%d\n",alphabet[i]);
            }
            if(i ==7){
                printf("C-:\t%d\n",alphabet[i]);
            }
            if(i ==8){
                printf("D:\t%d\n",alphabet[i]);
            }
            if(i ==9){
                printf("F:\t%d\n",alphabet[i]);
            }
        }
}
                                               



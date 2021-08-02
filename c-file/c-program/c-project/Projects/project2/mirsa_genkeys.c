/// file: mirsa_genkeys.c
/// description:
///    reads commandline arguments and checks the flag and returns messages based on the commandline
///and it creates random prime numbers  and pass it to the function in mirsa_lib.h to create oup and pvt keys as well as files for those keys
///
////// author: Gayathri Kanagaraj gk4045
/// since: 2020
///
// // // // // // // // // // // // // // // // // // // // // // // //


#include <stdio.h>
#include "mirsa_lib.h"
#include <getopt.h>
#include <stdlib.h>    // bool type
#include <limits.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

/// output a usage message/ to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print
void usage( char message[]) {
    fprintf( stderr, "%s", message );
}
/// output a note message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print
void error( char message[]) {
    
    fprintf( stderr, "%s", message);
    
}
///readFile function reads Primes.txt file, allocates memory for the
///unsigned long int array and stores values to the array.
/// @return pointer - unsigned long int pointer stored with  prime numbers 
unsigned long int* readFile(){
     unsigned long int *array;
     FILE *fp;
     fp =fopen("Primes.txt","r");
     int a=0;
     int str;
     if(fp == NULL){
     perror("Error");
     }
     int i =0;
     while(fscanf(fp,"%d",&str)!= EOF){
     	if(i==0){
	   
	   array = malloc(sizeof(unsigned long int) *str);
	}
	if(i>0){
	
        array[a]= str;
	a++;
	}
	i++;
     }
     
    fclose(fp);
    return array;
   
}
///generates random prime numbers 
///@param array - array of prime numbers
///@param seed - seed value to benerate random prime number
/// @return uint64_t prime number

void seedGen(unsigned long int *array, int seed,uint64_t *p,uint64_t *q){
        srand(seed);
        int randomIndex =rand()%100;
        *p=array[randomIndex];
        randomIndex =rand()%100;
        *q=array[randomIndex];
        
}	
///generates random prime numbers
///@param array - array of prime numbers
///@param t - time_t  value to benerate random prime number
/// @return uint64_t prime number

void tGen(unsigned long int *array, time_t t,uint64_t *p,uint64_t *q){
        srand(t);
        int randomIndex =rand()%100;
        *p=array[randomIndex];
	randomIndex =rand()%100;
        *q=array[randomIndex];

}
///generates key file name with .pvt at the end
///@param user - character array to store the generated file name
///@param keyname - char pointer for the keyname 
void makePvtFileName(char user[],const char* keyname){
	strcpy(user,keyname);
        strcat(user,".pvt");
}
///generates key file name with .pub at the end
///@param user - character array to store the generated file name
///@param keyname - char pointer for the keyname

void makePubFileName(char user[],const char* keyname){
        
        strcpy(user,keyname);
        strcat(user,".pub");
        
}




/// output a note message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param argc number of command line arguments
/// @param argv array of values of command line argument
/// @return int  EXIT-SUCCESS if successful completiion or EXIT _ERROR for for error.

int main(int argc, char * argv[]) {
  
   if(argc >=1){
        int opt;
        int seed;
        time_t t=0;
        int a =0;
        char keyname[513];
        if(argc == 1){
		 usage("missing test count\n");
                 usage("usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n");
                 exit( EXIT_FAILURE );
	
	}
        while((opt=getopt(argc,argv,"hvk:s:"))!= -1){
            switch (opt){
		    case 'h':
			usage("\nusage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n");
                    	return (EXIT_SUCCESS);
		    	break;
                case 'v':
		    mr_verbose(1);
                    
                    break;
                case 'k':
                    if(optarg != NULL){
                        strcpy(keyname,optarg);
                    }
                    else{
                       
                    }
                    break;
                case 's':
                    if(optarg){
                        if(isdigit(*optarg)){
                            seed =atoi(optarg);
                            a +=1;
                        }
                        else{
                            error("error: invalid seed value");
                            printf(" '%s'.\n",optarg);
                            usage("usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n");
                            return (EXIT_FAILURE);
			    break;
                        }
                    }
                    break;
                   
                case '?':
                    if(optopt =='k'){
                        usage("usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n");
                        return (EXIT_FAILURE);
                    }
                    if(optopt == 's'){
                       usage("usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n");
                       return (EXIT_FAILURE);
		    }
                    break;
             
                default:
		    	printf("missing test count");
                        usage("usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n");
                        exit( EXIT_FAILURE );
                }
        }
        for(; optind<argc;optind++){
            error("error: extra argument: ");
            printf("'%s'.\n",argv[optind]);
            usage("usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n");
            return(EXIT_FAILURE);
        }
	unsigned long int *array = readFile();
	uint64_t  p=0;
	uint64_t  q=0;
	int result =0;
	if(a>0){
		seedGen(array,seed,&p,&q);
		if(p ==q){
			seedGen(array,seed,&p,&q);
		}
		result = mr_make_keys(p,q,keyname);
		for(int i =0; i<3; i++){
			if(result==99){
				seedGen(array,seed,&p,&q);
                		result = mr_make_keys(p,q,keyname);
				if(i ==2){
					fprintf(stderr,"error: mr_make_keys: overflow. no keyset for <%lu, %lu>.\n",p, q);
					break;
				}
			}
			else{
				break;
			}
		}
	}

	else{
		tGen(array,t,&p,&q);
		if(p ==q){
                        tGen(array,t,&p,&q);
                }
		result = mr_make_keys(p,q,keyname);
                for(int i =0; i<3; i++){
                        if(result==99){
                                tGen(array,t,&p,&q);
                                result = mr_make_keys(p,q,keyname);
                                if(i ==2){
                                        fprintf(stderr,"error: mr_make_keys: overflow. no keyset for <%lu, %lu>.\n",p, q);
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }
	}
	if(array!=NULL){
                free(array);
        }
	char publickey[strlen(keyname)+5];
	char privatekey[strlen(keyname)+5];
        makePubFileName(publickey,keyname);
	makePvtFileName(privatekey,keyname);
	key_t  *publicKey;
	key_t *privateKey;
	if(result){
		publicKey = mr_read_keyfile(publickey);
        	privateKey =mr_read_keyfile(privatekey);
	}
	else{
		fprintf(stderr,"error: mr_make_keys: failed to generate keyset.\n");
	}
	if(publicKey !=NULL){
		free(publicKey);
	}
	 if(publicKey !=NULL){
                free(privateKey);
        }
	return (EXIT_SUCCESS);
   }	
   else{
  	return (EXIT_FAILURE);
  }
}


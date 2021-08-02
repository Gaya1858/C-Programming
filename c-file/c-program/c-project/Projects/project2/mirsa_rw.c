/// file: mirsa_rw.c
/// description:
//The mirsa_rw.c module is a main program that reads or writes cipherfiles 
//and plaintext based on the read or write flag on the command line.
/// it uses mirsa_lib.h  library functions to do the read and write process
/// -h: shows help message how to pass arguments from coomandline to run the program
/// -v: verbose
/// -k keyname: k flag has an argument of file name for private or public key(if not mentioned 
/// program will exit failure status
/// -r cipher [plain]: r flag read cipher and stdout the output if plain is not mentioned 
/// else writes into plain text file.
/// -w cipher [plain]: w flag reads plain file if given or stdin and encrypts it and stores 
/// in cipher file. 
////// author: Gayathri Kanagaraj gk4045
/// dated 11/06/2020
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

/// usage(). it is to display usage message to the user
/// it send the string with standard error format
/// uses fprintf for error
void usage(){
	fprintf(stderr,"\nusage:\n"
		"Reader use: mirsa_rw [-vh] [-k keyname] -r cipherfile [plainfile]\n"
		"\tIf plainfile is not provided, then reader output is to stdout.\n"
		"Writer use: mirsa_rw [-vh] [-k keyname] -w cipherfile [plainfile]\n"
		"\tIf plainfile is not provided, then writer input is from stdin.\n"
		"The -v flag turns on verbose output.\n");
}
/// read_file(fo,str), it reads plain text from file and stores in in a stri
/// string pointer.
///@param fp - file pointer for plai  text
///@patam str - plain text is stored in str pointer
void read_file(FILE *fp, char *str){
	char ch ='\0';
	int count =0;
	if(fp !=NULL){
		ch =fgetc(fp);
		while((ch!=EOF)){
			str[count] =ch;
			ch =fgetc(fp);
			count++;
		}
		str[count]='\0';
	}
}
///write_cipher(plain,fp,pubK), this function takes plain text
/// and encodes and encrpts the same into cipher file
///@param plain - string pointer for plain text
///@param fp - file pointer for cipher text
///@param pubK - key_t struct pointer for public key pair
/// encrpts plain text and writes into cipher text file
void write_cipher(char *plain, FILE *fp,key_t *pubK){
	uint64_t x = strlen(plain)-1;
	uint64_t count = x/4;
	uint64_t rest =x%4;
	uint64_t check =1;
	uint64_t reCheck =0;
	uint64_t i =0;
	if(count>0){
		char chunk[5];
		for(i =0; i<count*4; i+=4){
			chunk[0] = plain[i];
                        chunk[1] =plain[i+1];
                        chunk[2] =plain[i+2];
                        chunk[3]=plain[i+3];
                        chunk[4]='\0';
			check++;
			uint64_t enc =mr_encode(chunk);
			uint64_t encrp =mr_encrypt(enc,pubK);
			if(fp!=NULL){
				fwrite(&encrp,sizeof(uint64_t),1,fp);
			}
		}
	}
	if(rest >0 && count>0){
		char chunk[rest];
		i =count*4;
		for(uint64_t j =i;j<x;j++){
			chunk[reCheck] =plain[j];
			reCheck++;
		}if(reCheck ==rest){

			chunk[reCheck] ='\0';
			uint64_t enc =mr_encode(chunk);
			uint64_t encrp =mr_encrypt(enc,pubK);
			if(fp!=NULL){
                           fwrite(&encrp,sizeof(uint64_t),1,fp);
                        }
		}
	}
	if(count==0 && rest >0){
		char chunk[rest];
		for(uint64_t j =0;j<x;j++){
                      chunk[reCheck] =plain[j];
                      reCheck++;
                  }if(reCheck ==rest){
                      chunk[reCheck] ='\0';
		      uint64_t enc =mr_encode(chunk);
                      uint64_t encrp =mr_encrypt(enc,pubK);
		      if(fp!=NULL){
                          fwrite(&encrp,sizeof(uint64_t),1,fp);
                      }
		}
	}
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

/// main function checks all the flags and string arguments and returns valid 
/// error message if any. It uses mirsa_lid.h 
/// calls function according to the flags and shows output.
///@param argc - gives int value of commandline argument elements
///@param argv - character array storys command line arguments
///@return -  EXIT_SUCCESS for successful compliation and EXIT-FAILURE for no arguments in commandline
int main(int argc, char* argv[]){
	if(argc>1){
		int opt =0;
		int read =0;
		int write =0;
		int key =0;
		char file1[513];
		char kayname[513]=" ";
		char *file2=NULL;
		while((opt =getopt(argc,argv,"hvr:w:k:"))!= -1){
			switch(opt){
				case 'h':
					
					usage();
                			return(EXIT_FAILURE);

				case 'v':
					mr_verbose(1);
					break;
				case 'w':
					write =1;
					if(optarg != NULL){
						strcpy(file1,optarg);
					}
					break;
				case 'k':
                                        key =1;
                                        if(optarg != NULL){
                                                strcpy(kayname,optarg);
                                        }
                                        break;
				case 'r':
					read =1;
					if(optarg != NULL){
						strcpy(file1,optarg);
					}
                                        break;
				case '?':
					if(optopt =='w'){
						usage();
						return(EXIT_FAILURE);	
					}
					if(optopt =='r'){
                                	  	usage();
						return(EXIT_FAILURE);
					}
					if(optopt =='k'){
                                                usage();
                                                return(EXIT_FAILURE);
                                        }
					break;
				default:
					usage();
                                	return(EXIT_FAILURE);
					break;

			}
		
		}int count =0;
		for(;optind<argc;optind++){
			if(strlen(argv[optind])>0){
				file2 = malloc(sizeof(char)*strlen(argv[optind])+1);
				strcpy(file2,argv[optind]);
			}
			if(count>0){
				fprintf(stderr,"error: extra argument: '%s'.\n",argv[optind]);
                                usage();
				return(EXIT_FAILURE);
			}
			count++;
		}
		size_t x =strlen(kayname);
		char publickey[x+5];
                char privatekey[x+5];
       		makePubFileName(publickey,kayname);
       		makePvtFileName(privatekey,kayname);
		char plain[1025];
		if(write){
			char *keyN=NULL;
			if(key ==0){
				keyN = "user31.pub";
			}
			else{
				keyN = publickey;
			}
			key_t  *publicKey=NULL;
			publicKey=mr_read_keyfile(keyN);
			if(file2 !=NULL){
				FILE *fp;
				fp =fopen(file2,"r");
				if(fp !=NULL){
					read_file(fp,plain);
					FILE *fp1 =fopen(file1,"ab");
					write_cipher(plain,fp1,publicKey);
					fclose(fp1);
					fclose(fp);
				}
				else{
					fprintf(stderr,"error: miRSA could not read '%s' content.\n",file2);
				}

			
			}
			else{
    				fgets(plain, 1025, stdin);
				FILE *fp1 =fopen(file1,"ab");
				write_cipher(plain,fp1,publicKey);
				fclose(fp1);
			}
			if(publicKey !=NULL){
				free(publicKey);
			}
		}
		if(read){
			char *keyN=NULL;
			if(key ==0){
                                keyN = "user31.pvt";
                        }
                        else{
                                keyN = privatekey;
                        }
			key_t  *privateKey =NULL;
			privateKey =mr_read_keyfile(keyN);
			
                        if(file1 !=NULL){
                                FILE *fp;
                                fp =fopen(file1,"rb");
                                uint64_t crypt =0;
				if(fp !=NULL){
					while(fread(&crypt,sizeof(uint64_t),1,fp)!=0){
						uint64_t decrp =mr_decrypt(crypt,privateKey);
						char *plain = mr_decode(decrp);
						if(file2!=NULL){
							FILE *fp1;
                                			fp1 =fopen(file2,"a");
							if(fp1!=NULL){
								fputs(plain,fp1);
								if(plain!= NULL){
                                                        		free(plain);}
								fclose(fp1);
							}
						}
						else{
                       					printf("%s",plain);
							if(plain!= NULL){
                        					free(plain);}}
                			}
					fclose(fp);
                                }
                                else{
                                        fprintf(stderr,"error: miRSA could not read '%s' content.\n",file1);
                                }


                        }
			if(privateKey !=NULL){
				free(privateKey);
			}
                }
		if(file2!=NULL){
                	free(file2);
                 }
		return(EXIT_SUCCESS);
	}
	else{
		fprintf(stderr,"error: missing file argument\n");
		fprintf(stderr,"usage:\n"
                "Reader use: mirsa_rw [-vh] [-k keyname] -r cipherfile [plainfile]\n"
                "\tIf plainfile is not provided, then reader output is to stdout.\n"
                "Writer use: mirsa_rw [-vh] [-k keyname] -w cipherfile [plainfile]\n"
                "\tIf plainfile is not provided, then writer input is from stdin.\n"
                "The -v flag turns on verbose output.\n");
		return(EXIT_FAILURE);

	}
}

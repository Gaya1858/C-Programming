/// file: file_bitsets.c
/// description:
///  it reads command line argument as follows
///  -e and 2 string or fine name will encode the strings int he file and the string.
///  -i and 2 values - will return sets_cintersection
///  -c and 2 values - will return set_complement
///  -n and 2 values -will return set_cardinality
///  -u and 2 values - will return set_union
///  -m and 2 values -will return member of set
///
///author: Gayathri Kanagaraj gk4045
/// dated : 10/27/2020
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // uint64_t type
#include <unistd.h>
#include <errno.h>
#include <getopt.h> // getopt function for flag processing
#include <limits.h>

#define uint64_t unsigned long int

char ascii[65] =".,0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
const size_t SETSIZE = sizeof( uint64_t ) << 3 ;

/// its encodes the given file and returns uint64_t in sucess
/// else return perror
/// it loops through char by char in the file and sets the bit on 
/// based on the charater it reads.
/// once file reading done, it loops through the setbit array and adds the setbit value
/// to an uint64_t variable -set.
/// @param fp FILE pointer 
/// @return uint64_t as a encoded set
uint64_t file_set_encode( FILE * fp ){
	char ch ='\0';
	uint64_t bitset[64];
	uint64_t set =0;
	uint64_t count =0;
	if(fp !=NULL){
		for(int i =0; i<64;i++){
                	bitset[i]=0;
        	}
		ch =fgetc(fp);
		while((ch !=EOF)){
			for(int i = 0; i<64;i++){
				
				if(ch ==ascii[i]){
					bitset[i]=1;
					break;
				}
			}
			ch =fgetc(fp);
		}
	
	   for(int i =0; i<=63; i++){
                	if(bitset[i] ==1){
                    		count = (uint64_t)1<<i;
				set +=count;
            		}
			if(i ==63 && bitset[i] ==1){
				set = ULONG_MAX;
			}
           }
	}
	else{
		perror("Error ");
		return EXIT_FAILURE;
	}
	return set;
}
/// its encodes the given string and returns its uint64_t value
/// it loops through char by char in the given string and sets the bit on 
/// based on the charater it reads.
/// once string reading done, it loops through the setbit array and adds the setbit value
/// to an uint64_t variable -set.
/// @param st char pointer 
/// @return uint64_t as a encoded set
uint64_t set_encode( char *st){
        uint64_t bitset[64];
        uint64_t set =0;
        uint64_t count =0;
	size_t x =strlen(st);
	for(int i =0; i<64;i++){
		bitset[i]=0;
	}
	for(uint64_t i =0; i<x;i++){
	
		for(int j = 0; j<64;j++){
                                if(st[i] == ascii[j]){
                                        bitset[j]=1;
					break;
				}
                 }
	}
	for(int i =0; i<64; i++){
        	if(bitset[i] ==1){
                    count = (uint64_t)1<<i;
                    set +=count;
		    count =0;


            	}
        }
	return set;
}
/// it takes uint64_t value and converts as character and returns the char pointer
/// first it bitmasks the passed value and loop through bit by bit checking 
/// whether it is on or off, if on it takes the value from ascii array and stores in a char*
/// @param set uint64_t value
/// @return pointer character pointer of the member set
char *set_members(uint64_t set){
	char *str=NULL;
	char temp[65];
	
	uint64_t mask=0;
	int count =0;
	int num =0;
	for(mask =set; mask !=0; mask>>=1){
		if(mask &1){
			temp[num] =ascii[count];
			num++;
		}	
		count++;
	}
    	temp[num] ='\0';
	int a =num-1;
	str = malloc(sizeof(char)*strlen(temp)+1);
	
	
	for(int i =0; i<num;i++){
		str[i]=temp[a];
		a--;
	}
	str[num]='\0';	
	return str;

}
/// it takes uint64_t value and returns the cardinality of the bit value
/// @param set uint64_t value
/// @return size_t value for cardinality of the set
size_t set_cardinality( uint64_t set ){

	size_t num =0;
	uint64_t mask=0;
        for(mask =set; mask !=0; mask>>=1){
                if(mask &1){
                        num++;
                }
        }

	return num;
}
/// it takes uint64_t value and returns its complement of the value
/// @param set uint64_t value
/// @return uint64_t complement  value of the passed argument
uint64_t set_complement( uint64_t set1 ){
	uint64_t comp =~set1;
	return comp;

}
/// it takes two uint64_t values and returns union that those sets
/// @param set1 uint64_t value
///@param set2 uint64_t value
/// @return uint64_t set_union of those passed values
uint64_t set_union( uint64_t set1, uint64_t set2 ){
	uint64_t uni =0;
	uint64_t count =0;
	uint64_t mask2 =set1;
	uint64_t mask3 =set2;
	uint64_t temp =0;
	 while((count <=SETSIZE)){
                temp = (uint64_t)1 << count;	
		if((mask2&1) |(mask3&1)){
			uni+=temp;
		}
		mask2>>=1;
		mask3>>=1;
		count++;
	}
	return uni;

}
/// it takes two uint64_t values and returns intersection of  those sets
/// @param set1 uint64_t value
///@param set2 uint64_t value
/// @return uint64_t set_intersect of those passed values
uint64_t set_intersect( uint64_t set1, uint64_t set2 ){
	uint64_t uni =0;
        uint64_t count =0;
        uint64_t mask2 =set1;
        uint64_t mask3 =set2;
        uint64_t temp =0;
        while((count <=SETSIZE)){
		temp = (uint64_t)1 << count;
                if((mask2&1) &(mask3&1)){
                        uni+=temp;
			temp =0;
                }
                mask2>>=1;
                mask3>>=1;
                count++;
        }
        return uni;

}
/// main function checks all the flags and string arguments and returns valid 
/// error message if any.
/// calls function according to the flags and shows output.
/// all the functions are mentioned above 
///@param argc - gives int value of commandline argument elements
///@param argv - character array storys command line arguments
///@return -  EXIT_SUCCESS for successful compliation and EXIT-FAILURE for no arguments in commandline
int main(int argc, char * argv[]) {
    if(argc >1){
        int opt=0;
	int hex=0;
	int enc =0;
	int inter =0;
	int comp =0;
	int car=0;
	int mset =0;
	int uni =0;
	char *str1=NULL;
	char *str2=NULL;
        while((opt=getopt(argc,argv,":xeicnmu"))!= -1){
            switch (opt){
                case 'x':
		    hex =1;	
		    break;
                case 'e':
                    enc =1; 
                    break;
                case 'i':
		    inter =1;
                    break;
		case 'c':
		    comp =1;
                    break;
		case 'n':
		    car =1;
                    break;
		case 'm':
		    mset =1;
                    break;
		case 'u':
                    uni =1;
                    break;
                case '?':
		   fprintf(stderr,"%s: invalid option -- '%c'\n",argv[0],optopt);
		    fprintf(stderr,"Usage: file_bitsets -[ceimnux] [--] str1 str2\n"
				    "\tIf str1 is negative, then add '--' before str1 to stop flag processing.\n");
		    return(EXIT_FAILURE);
		default:
                    fprintf(stderr,"Usage: file_bitsets -[ceimnux] [--] str1 str2\n"
                                    "\tIf str1 is negative, then add '--' before str1 to stop flag processing.\n");
                    return(EXIT_FAILURE);
                }
        }
	if(!enc&&!inter&&!comp&&!car&&!mset&&!uni){
		fprintf(stderr,"Usage: file_bitsets -[ceimnux] [--] str1 str2\n"
   "\tIf str1 is negative, then add '--' before str1 to stop flag processing.\n");
		return(EXIT_FAILURE);
	}
	int count =0;
        for(; optind<argc;optind++){
		if(count ==0){
			if(strcmp(argv[optind],"--")){
				str1 = malloc(sizeof(char)*(strlen(argv[optind])+1));
				strcpy(str1,argv[optind]);
				count =100;		
			}
			else{
				str1 = malloc(sizeof(char)*(strlen(argv[optind])+1));
				strcpy(str1,argv[optind]);
			}
		}
		 if(count ==1 || count ==101){
			str2 = malloc(sizeof(char)*(strlen(argv[optind])+1));
                        strcpy(str2,argv[optind]);
                }
		count++;
        }
	if(str2 ==NULL){
		fprintf(stderr,"Usage: file_bitsets -[ceimnux] [--] str1 str2\n"
                "\tIf str1 is negative, then add '--' before str1 to stop flag processing.\n");
		return(EXIT_FAILURE);
	}
	uint64_t set1 =0;
	uint64_t set2 =0;
	if(enc){
		FILE *fp=NULL,*fp1=NULL;
		fp =fopen(str1,"r");
		if(fp!=NULL){
			set1 =file_set_encode(fp);
			printf("string1:\t%s\tEncoding the file:\t%s\n",str1,str1);
			fclose(fp);
		}
		else{
			set1=set_encode(str1);
			printf("string1:\t%s\tEncoding the string:\t%s\n",str1,str1);
		}
		fp1 =fopen(str2,"r");
        	if(fp1 !=NULL){
                	set2=file_set_encode(fp1);
			printf("string2:\t%s\tEncoding the file:\t%s\n",str2,str2);
			fclose(fp1);
        	}
       	 	else{
                	set2 =set_encode(str2);
			printf("string2:\t%s\tEncoding the string:\t%s\n",str2,str2);
       		}
		printf("set1:\t0x%016lx\n",set1);
		printf("set2:\t0x%016lx\n",set2);
		printf("\n");	
	}
	char *mset1=NULL;
	char *mset2=NULL;
	if(hex && mset){
		uint64_t m =0;
		sscanf(str1,"%lx",&m);
		printf("set1:\t0x%016lx\n",m);
		mset1=set_members(m);
		m =0;
		sscanf(str2,"%lx",&m);
		printf("set2:\t0x%016lx\n",m);
		mset2 =set_members(m);
		printf("members of set1:\t'%s'\n",mset1);
		printf("members of set2:\t'%s'\n",mset2);
		if(mset1 != NULL){
                	free(mset1);}
         	if(mset2 != NULL){
                	free(mset2);}
	}
	else if(!hex && mset){
                uint64_t m =0;
                sscanf(str1,"%lu",&m);
		printf("set1:\t0x%016lx\n",m);
                 mset1=set_members(m);
                m =0;
                sscanf(str2,"%lu",&m);
                printf("set2:\t0x%016lx\n",m);
		mset2 =set_members(m);
		printf("members of set1:\t'%s'\n",mset1);
                printf("members of set2:\t'%s'\n",mset2);
		if(mset1 != NULL){
                        free(mset1);}
                if(mset2 != NULL){
                        free(mset2);}
        }
	size_t a =0;
	size_t b =0;
	if(hex && car){
                uint64_t m =0;
                sscanf(str1,"%lx",&m);
		printf("set1:\t0x%016lx\n",m);
                a=set_cardinality(m);
		m =0;
                sscanf(str2,"%lx",&m);
                printf("set2:\t0x%016lx\n",m);
                b =set_cardinality(m);
		printf("set1 set_cardinality:\t%lu\n",a);
        	 printf("set2 set_cardinality:\t%lu\n",b);}
        else if(!hex && car){
                uint64_t m =0;
                sscanf(str1,"%lu",&m);
                printf("set1:\t0x%016lx\n",m);
                a=set_cardinality(m);
                m =0;
                sscanf(str2,"%lu",&m);
                printf("set2:\t0x%016lx\n",m);
                b=set_cardinality(m);
                printf("set1 set_cardinality:\t%lu\n",a);
		printf("set2 set_cardinality:\t%lu\n",b);
        }
	if(hex && comp){
                uint64_t m =0;
                sscanf(str1,"%lx",&m);
                printf("set1:\t0x%016lx\n",m);
                set1=set_complement(m);
                m =0;
                sscanf(str2,"%lx",&m);
                printf("set2:\t0x%016lx\n",m);
                set2=set_complement(m);
               printf("set1 set_complement:\t0x%016lx\n",set1); 
	       	printf("set2 set_complement:\t0x%016lx\n",set2);}
        else if(!hex && comp){
                uint64_t m =0;
                sscanf(str1,"%lu",&m);
                printf("set1:\t0x%016lx\n",m);
                set1=set_complement(m);
                m =0;
                sscanf(str2,"%lu",&m);
                printf("set2:\t0x%016lx\n",m);
                set2=set_complement(m);
		printf("set1 set_complement:\t0x%016lx\n",set1);
                printf("set2 set_complement:\t0x%016lx\n",set2);
        }
	if(hex && uni){
                uint64_t m =0;
                sscanf(str1,"%lx",&m);
                printf("set1:\t0x%016lx\n",m);
                uint64_t n =0;
                sscanf(str2,"%lx",&n);
                printf("set2:\t0x%016lx\n",n);
                set2=set_union(m,n);
               printf("set_union:\t0x%016lx\n",set2);
	}else if(!hex && uni){
                uint64_t m =0;
                sscanf(str1,"%lu",&m);
                printf("set1:\t0x%016lx\n",m);
                uint64_t n =0;
                sscanf(str2,"%lu",&n);
                printf("set2:\t0x%016lx\n",n);
                set2=set_union(m,n);
                printf("set_union:\t0x%016lx\n",set2);
        }
	 if(hex && inter){
                uint64_t m =0;
                sscanf(str1,"%lx",&m);
                printf("set1:\t0x%016lx\n",m);
                uint64_t n =0;
                sscanf(str2,"%lx",&n);
                printf("set2:\t0x%016lx\n",n);
                set2=set_intersect(m,n);
               printf("set_intersect:\t0x%016lx\n",set2);
        }else if(!hex && inter){
                uint64_t m =0;
                sscanf(str1,"%lu",&m);
                printf("set1:\t0x%016lx\n",m);
                uint64_t n =0;
                sscanf(str2,"%lu",&n);
                printf("set2:\t0x%016lx\n",n);
                set2=set_intersect(m,n);
                printf("set_intersect:\t0x%016lx\n",set2);
        }
	if(str1 != NULL){
	 	free(str1);}
	 if(str2 != NULL){
	 	free(str2);}
	return(EXIT_SUCCESS);
    }
    else{
	fprintf(stderr,"Usage: file_bitsets -[ceimnux] [--] str1 str2\n"
                "\tIf str1 is negative, then add '--' before str1 to stop flag processing.\n");
    	return (EXIT_FAILURE);
    }
}

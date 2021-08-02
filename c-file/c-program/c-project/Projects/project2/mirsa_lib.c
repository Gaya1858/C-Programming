/// this classes implements  mirsa_lib.h libraray methods 
/// 
/// author: Gayathri Kanagaraj gk4045
/// dated: 11/15/2020
///
// // // // // // // // // // // // // // // // // // // // // // // //
#include <stdint.h>     // uint64_t typedef
#include <stdbool.h>    // bool type
#include <limits.h>
#include "mirsa_lib.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
/// mr_verbose( bool value ) sets a flag to print diagnostic information.
/// Verbose content prints to stdout.
/// @param value boolean value; false turns verbose off. true turns verbose on.
/// @return old value of verbose

bool mr_verbose( bool value ){
	if(value){
		printf("This is a program for Miniature RSA algorithm!");
	}
	return 0;

}
/// creates n( nonce) which is product of p and q
/// if nonce is bigger than uint64_t then it will return false
/// else will return true, will create a private and public keys.
/// if error creating keys, program will return false else true.
/// if true key files will created based on the user name and store the key pai
/// else it will exist if the key files already exists.
/// @param p prime number for key generation
/// @param q prime number for key generation
/// @param user string that will be the 'user' in 'user.pub' file name
/// @return true if the keys are made false if it fils to create key
/// @see limits.h for the maximum

bool mr_make_keys( uint64_t p, uint64_t q, const char * user ){
	uint64_t n  = p*q;
	uint64_t phi=0;
	int fal =1;
	char pub[strlen(user)+5];
        strcpy(pub,user);
	strcat(pub,".pub");
	char pri[strlen(user)+5];
        strcpy(pri,user);
        strcat(pri,".pvt");
	uint64_t d =0;
	if(__builtin_umull_overflow( p, q, &n)){
	    fal=99;
            return fal;
	}
	else{	uint64_t e =3; uint64_t k =1;
		phi = (p-1)*(q-1);
		for(uint64_t i =e; i<10; i++){
			for(uint64_t j =k; j<10; j++){
			
				if((1+(j*phi))%i ==0){
					d = (1+(j*phi))/i ;
					e =i;
					break;
				}
			}
			if(i==10){
				fprintf(stderr,"error: mr_make_keys: no keyset for <%lu, %lu>.\n", p, q);
				fal=0;
				return fal;;
			}
		}
		if(fal==1){
			FILE *public, *private;
		 	private = fopen(pri,"wb");
		 	public =fopen(pub,"wb");
			if(private != NULL || public !=NULL){			
				key_t value,value1;
				value.key = e;
				value.nonce =n;
				fwrite(&value,sizeof(value),1,public);
				value1.key =d;
                        	value1.nonce =n;
                        	fwrite(&value1,sizeof(value1),1,private);
				fclose(public);
                        	fclose(private);
			}
		}
	}

	return fal;
}


/// mr_read_keyfile  takes the file name and read the file and
/// stores value from the file to the key_t struct and returns it
///  
/// @param file_name the string file name of a miRSA key file
///
/// @return a key_t pointer to a heap-allocated key object or NULL on error

key_t * mr_read_keyfile( const char * file_name ){
	FILE *fp;
	key_t  *keystruct;
	fp =fopen(file_name,"rb");
	if(fp != NULL){
		keystruct = malloc(sizeof(key_t));
		fread(keystruct,sizeof(key_t),1,fp);
		fclose(fp);
	
	}
	else{
		keystruct =NULL;
		fprintf(stderr,"error: mr_read_keyfile: '%s': %s\n",file_name, strerror(errno));
	}
	return keystruct;
}
/// mr_encrypt( p, pubkey) uses pubkey to encrypt the message encoded in p.
/// Encrypt the encoded message, p, using public key pair pubkey(e, n).
///this function uses modular exponantiation to get the 
/// encrypt  value. if c > n then return error msg and exit failure. Also checks 
/// overflow when computing modular exponantiation.. if overflow oocurs the 
/// return error msg and exit failure
/// @param p an unsigned long value representing an encoded message
/// @param pubkey a pointer to a pubkey
/// @return encrypted cipher, c, representing p, or 0 for failure to encrypt
uint64_t mr_encrypt( uint64_t p, const key_t * pubkey){
    uint64_t plain =1;
    uint64_t e = pubkey ->key;
    uint64_t n = pubkey ->nonce;
    if(p> n){
        fprintf(stderr,"error: p value [%lu] is a greater then n [%lu]\n",p,n);
        return EXIT_FAILURE;
    }
    uint64_t mask  =e;
    uint64_t count =0;
    size_t setsize = sizeof(uint64_t)<<3;
    uint64_t extra[64];
    uint64_t ad =0;
    int w =0;
    while(count < setsize){
        uint64_t temp =(uint64_t)1<<count;
        if((mask &1)&& (ad <=e)){
                uint64_t x =1,y=p;
                while(temp>0){
                        if(temp%2 ==1){
                                x =(x*y)%n;
                        }
                        y =(y*y)%n;
                        temp/=2;
                }
                x =x%n;
                extra[w] =x;
                w++;
                ad+=temp;
                if(ad == e){
                        break;
            }
        }
        count++;
        mask>>=1;
    }

    for(int i =0; i<w; i++){
        plain = (plain*extra[i]) %n;
        if(__builtin_umull_overflow( plain, 1, &plain)){
                fprintf(stderr,"error: mr_encrypt: code overflow.\n");
            return EXIT_FAILURE;;
        }
    }
    return plain;

}


/// mr_decrypt( c, pvtkey) - this function uses modular exponantiation to get the 
/// decrpyt value. if c > n then return error msg and exit failure. Also checks 
/// overflow when computing modular exponantiation.. if overflow oocurs the 
/// return error msg and exit failure
/// Decrypt the encrypted cipher, c, using the private key pair pvtkey(d, n).
/// @param c an unsigned long value representing an encrypted cipher
/// @param pvtkey a pointer to a pvtkey
/// @return decrypted value, p, that represents c

uint64_t mr_decrypt( uint64_t c, const key_t * pvtkey){
    uint64_t plain =1;
    uint64_t d = pvtkey ->key;
    uint64_t n = pvtkey ->nonce;
    if(c> n){
    	fprintf(stderr,"error: c value [%lu] is a greater then n [%lu]\n",c,n);
	return EXIT_FAILURE;
    }
    uint64_t mask  =d;
    uint64_t count =0;
    size_t setsize = sizeof(uint64_t)<<3;
    uint64_t extra[64];
    uint64_t ad =0;
    int w =0;
    while(count < setsize){
        uint64_t temp =(uint64_t)1<<count;
        if((mask &1)&& (ad <=d)){
            	uint64_t x =1,y=c;
            	while(temp>0){
                	if(temp%2 ==1){
                    		x =(x*y)%n;
                	}
                	y =(y*y)%n;
                	temp/=2;
            	}
            	x =x%n;
            	extra[w] =x;
            	w++;
            	ad+=temp;
		if(ad == d){
                	break;
            }
        }
        count++;
        mask>>=1;
    }
    for(int i =0; i<w; i++){
        plain = (plain*extra[i]) %n;
	if(__builtin_umull_overflow( plain, 1, &plain)){
         	fprintf(stderr,"error: mr_decrypt: cipher overflow.\n");
            return EXIT_FAILURE;;
        }
    }
    return plain;
}


/// mr_encode( const char * st) converts string to an unsigned long code.
/// mr_encode uses a simple, left-to-right encoding.
/// mr_encode simply converts the string to a hexadecimal 'string' that
/// has two hexadecimal 'digits' per character, and
/// returns that string as an unsigned long integer.
///
/// @param st a NUL-terminated, string to encode
/// @return an unsigned long value representing the string as a number

uint64_t mr_encode( const char * st){
	uint64_t m =0;
	char str[strlen(st)+1];
	int  ch =0;
	int i =0;
	uint64_t n =0;
	uint64_t add =0;
	while(st[ch] !='\0'){
		sprintf((char*)(str+i),"%02x",st[ch]);
		ch +=1;
		i+=2;
	}
	sscanf(str,"%lx",&m);
	n = ULONG_MAX -m;
	add =m+n;
	if(__builtin_uaddl_overflow(m,n,&add)){
		fprintf(stderr,"error: mr_encode: code doesn't fit in uint64_t '%s'.\n",st);
		return EXIT_FAILURE;		
	}
	return m;
}


/// mr_decode( code) converts an unsigned code to string.
/// mr_decode simply converts the code back to its original string.
/// The caller is responsible for freeing the string object when finished.
/// @param code an unsigned, encoded value previously produced by mr_encode
/// @return a pointer to the resulting C string, a heap-allocated value

char * mr_decode( uint64_t code){
	char st[65];
	int b=0;
       	b=sprintf(st,"%lx",code);
	int a =0;
	a=b/2;
	char *str=calloc(a+1,sizeof(char));
	int i =0;
	i=b-1;
	a =a-1;
	while(i>0){
		char c[3];
		c[0] =st[i-1];
		c[1] =st[i];
		c[2] ='\0';
		uint64_t x =0;
		sscanf(c,"%lx",&x);
		char d =(char) x;
		str[a] =d;
		i =i-2;
		a =a-1;
	}
	return str;
	

}


///
///  String.c
///  hw6
/// this String.c class implemets methods which manipulates the STring struct in String.h
///  Created by Gayathri Kanagaraj on 10/15/20.
///

#include "String.h"
#include <stdlib.h>
#include <assert.h>
struct string_s{
    size_t capacity;
    size_t length;
    char *strData;
    
};
/// Create a String entity.
///
/// Strings have three important characteristics:  capacity, length,
/// and contents.  The capacity of a String is the maximum number of
/// characters it can contain.  The length of the String is the number of
/// characters it currently contains.  The contents of the String are the
/// actual characters it contains.  Initial capacity is determined by the
/// 'size' parameter, initial length by the 'length' parameter, and
/// contents by the 'data' parameter.
///
/// If 'size' is 0, 'length' and 'data' are ignored, and a zero-length
/// String with a capacity of zero is created.
///
/// If 'size' is > 0, a String of capacity MAX(size,length) is created.
/// If 'length' is zero or 'data' is NULL, the initial contents will be
/// no characters (i.e., its initial length is zero); otherwise the
/// first 'length' bytes from 'data' are copied in as the initial
/// contents, and the length is 'length'.  (Note: the capacity can be
/// greater than the length, but the reverse is not possible.)
///
/// @param size   An initial capacity for the String
/// @param length An initial length for the String
/// @param data   An array of bytes to be used as the initial contents
///
/// @return The created String, or NULL if some error other than an
///    allocation failure occurs.
/// @exception If space for the String cannot be allocated, the program
///    terminates with an appropriate error message.
String str_create( size_t size, size_t length, const unsigned char *data ){
    
   String newString;
    
    newString = malloc(sizeof(struct string_s));
    if(size ==0){
        newString -> capacity =0;
        newString -> length =0;
        newString -> strData =NULL;
    }
    else{
        if(length>size){
            newString -> capacity =length;
        }
	else{
	   newString -> capacity = size;
	}
        newString -> length =length;
        newString ->strData = malloc(sizeof(char)*newString->capacity);
        for(size_t  i =0; i<length;i++){
            newString->strData[i] =data[i];
    	}
    }
    assert(newString !=NULL);
    
    return newString;
    
}
///
/// Tear down and deallocate the supplied String.
///
/// @param str   The String to be deleted
///
/// @pre str must be a valid String
///
void str_destroy( String str ){
	if(str != NULL){	
	     free(str->strData);
             free(str);
	}

}
///
/// Create a C-style string from the supplied String.
///
/// Dynamically allocates space for a copy of the data found in
/// the String parameter plus a trailing NUL byte, and returns
/// the pointer to that space.
///
/// @param str   The String to be duplicated
///
/// @pre str must be a valid String
///
/// @return The created C-style string
///
/// @exception If space for the String cannot be allocated, the program
///    terminates with an appropriate error message.
///
char *str_to_c( const String str ){
	char *cString;

	if(str !=NULL){
	   cString = malloc((str->length+1)*sizeof(char));
	   for(size_t i = 0; i<str->length;i++){
   	        cString[i]=str->strData[i];
	   }
	  cString[str->length] = '\0';
		
	}
	assert(cString !=NULL);
	return cString;
}
///
/// Return the length of the supplied String.
///
/// @param str    The String to examine
///
/// @pre str must be a valid String
///
/// @return The number of characters in the String
///
size_t str_length( const String str ){
     size_t strLength=0;
     if(str !=NULL){
     	strLength = str ->length; 
     
     }
	return strLength;
}

///
/// Reverse an existing string.
/// @param src    The String to be reversed
///
/// @pre str must be a valid String
///
/// @return A new String containing the reversed original String
///
/// @exception If space for the String cannot be allocated, the program
///    terminates with an appropriate error message.
///
String str_reverse( const String str ){

	String  rString;
	if(str !=NULL){
		rString =malloc(sizeof(struct string_s));
		rString->length = str->length;
		rString->capacity = str->capacity;
		rString ->strData = malloc(sizeof(char)*str->capacity);
		size_t x =str->length;
		for(size_t i =0; i <str->length;i++){
			x--;
			rString->strData[i] = str->strData[x];
			
		
		}
	
	}
	assert(rString !=NULL);
	return rString;

}

///
/// Copy one string into another, replacing its contents.
///
/// If the capacity of the destination String is too small, it will
/// be grown to be large enough to hold the copied data.
///
/// @param dst    The String to be replaced
/// @param src    The String to be copied
///
/// @pre str must be a valid String
///
/// @return The number of characters that were copied.
///
size_t str_copy( String dst, const String src ){
	size_t numchar=0;
	if(src != NULL){
		if( dst -> capacity >= src-> capacity){
			dst->length = src->length;
			dst ->capacity = src->capacity;
			for(size_t i  =0; i<dst->length; i++){
			      	dst->strData[i] = src->strData[i];
			        numchar++;
			}
			
		}
		else{   size_t x =src->length  - dst->length;
                        dst ->capacity = src->capacity;
			dst->strData = realloc(dst->strData,x*sizeof(char));
			
			for(size_t i  =0; i<src->length; i++){
                                	dst->strData[i] = src->strData[i];
					numchar++;}


                        
			dst->length = src->length;
	
                
		}
	}
	return numchar;

}

///
/// Concatenate one string to another.
///
/// Appends the source String to the destination String.  If the
/// capacity of the destination String is too small, it will be
/// grown to contain the additional data.
///
/// @param dst    The String to be modified
/// @param src    The String to be appended
///
/// @pre src must be a valid String
/// @pre dst must be a valid String
///
/// @return The number of characters in the resulting string.
///
size_t str_concat( String dst, const String src ){
	size_t x = dst->length ;
	size_t a =0;
	if(dst!= NULL &&src!=NULL){
		dst ->strData =realloc(dst->strData,(dst->length+src->length)*sizeof(char));
	 	for(size_t i  =x; i<(dst->length+src->length); i++){	
                     
			dst->strData[i] = src->strData[a];
		     		x++;			
				a++;
		}
		dst->length =x;
		if(dst->length > dst->capacity){
			dst-> capacity = dst->length;}

		dst ->capacity =dst->capacity +src -> capacity;
		
	}
	return x;

}
///
/// Compare two strings, returning an integer indicating the result
/// of the comparison.
///
/// Returns a negative value if str1 < str2, zero if they are equal,
/// and a positive value if str1 > str2.
///
/// @param str1    The first String to be examined
/// @param str2    The second String to be examined
///
/// @pre str1 must be a valid String
/// @pre str2 must be a valid String
///
/// @return A value indicating the relationship between the strings
///
int str_compare( const String str1, const String str2 ){
	
	int comp ;

	if(str1 != NULL && str2!= NULL){
		
		if((str1->strData < str2->strData)){
                        comp = -1;
                }
                if((str1->strData > str2->strData)){
                        comp = 1;
                }
                if((str1->strData == str2->strData)){
                        comp = 0;
                }

	
	}
	return comp;


}

///
/// Return the character at a specific position in the String.
///
/// Indices are enumerated from either end of the string.  Non-negative
/// values are indices from the beginning of the string; negative
/// values are indices from the end of the string.  As an example:
///
///     + index      0   1   2   3   4
///     string       H   e   l   l   o
///     - index     -5  -4  -3  -2  -1
///
/// @param str    The String to be examined
/// @param index  The index of the desired character
///
/// @pre str must be a valid String
///
/// @return The selected character; if that character does not exist
///    (i.e., the index is out of bounds), returns STR_ERROR
///
int str_char_at( const String str, int index ){

	char ch =-1;
	if(str != NULL){
		if(index>=0){
			for(int i =0; i<=index; i++){
				if(i ==index){
					ch = str->strData[i];
				}
			}
		
		}
		else{	size_t j =str->length-1;
			for(int i = -1; i<=index; i--){

                                if(i ==index){
                                        ch = str->strData[j];
                                }
				j--;
                        }
		
		}
	}
	if(ch < 0){
	 return STR_ERROR;
	}
	else
		return ch;

}

///
/// Extract a substring from an existing String.
///
/// Creates a new String object which contains a substring from
/// the contents of an existing String object, as specified by
/// starting and ending indices.
///
/// @param str   The String to be examined
/// @param start The starting index
///
/// @param end   The ending index
///
/// @pre str must be a valid String
///
                                                              
/// @return A new String object containing the substring str[start..end]
///    from the str parameter, or NULL if an error occurs. (This failure
///    does not cause termination of the program.)
///
/// @exception If space cannot be allocated for the new String, the
///    program terminates with an appropriate error message.
///
String str_substring( const String str, int start, int end ){
        String subString;
	size_t len =0;	
	if(str !=NULL){
		int x =0;
		size_t a =0;
		subString =malloc(sizeof(struct string_s));
		subString->capacity = str->capacity;
		if(start>=0 &&end >=0){
			len =(end -start)+1;
			subString ->length = len;
			subString->strData =malloc(sizeof(char)*len);
			for(int i =start; i<=end; i++){
				subString->strData[x] =str->strData[i];
				x++;
		
			}
		}
		if(start <0&& end <0){
			len =(end - start)+1;
			int y = -str->length;
			subString ->length = len;
			subString->strData =malloc(sizeof(char)*len);
                        for(int i =y; i<=-1; i++){

				if(i >=start && i<=end){
                                	subString->strData[a] =str->strData[x];
                            	    	a++;
				}
				x++;
                        }

		}
		if(start >=0 && end <0){
                        len =((str->length +end)-start)+1;
                        int y = -str->length;
			int b =str->length;
			subString->strData =malloc(sizeof(char)*len);
                        subString ->length = len;
                        for(int i =0; i <b; i++){

                                if(i >=start && y<=end){
                        	        subString->strData[a] =str->strData[i];
					a++;
                                }
                                y++;
                        }

                }
		if(start <0 && end >=0){
                        len =((str->length +end)-start)+1;
                        int y = -str->length;
                        subString ->length = len;
			subString->strData =malloc(sizeof(char)*len);
                        for(int i =y; i <=-1; i++){

                                if(i >=start && x<=end){
                                subString->strData[a] =str->strData[x];
				a++;
                                }
                                x++;
                        }

                }
	}
	assert(subString!=NULL);
	return subString;
}


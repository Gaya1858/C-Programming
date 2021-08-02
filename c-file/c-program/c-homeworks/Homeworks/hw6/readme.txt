 I have run the following and find some differences,

strTest1 using valgrind --leak-check=full ./strTest1 , no memory leak or error,
strTest2 using valgrind --leak-check=full ./strTest2 , no memory leak or error,
strTest3 using valgrind --leak-check=full ./strTest3 , no memory leak or error,
RUN using valgrind --leak-check=full ./RUN, Heap summary says “ in use at exit: 96 allocated and 50 frees, 26297 bytes allocated” . But in the error summary - 0 errors from 0 contexts


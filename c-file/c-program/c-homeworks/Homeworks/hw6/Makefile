#
# Created by gmakemake (Ubuntu Jul 25 2014) on Mon Oct 19 15:59:26 2020
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS = -std=c99 -ggdb -Wall -Wextra -pedantic

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	String.c strTest1.c strTest2.c strTest3.c
PS_FILES =	
S_FILES =	
H_FILES =	String.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	String.o 

#
# Main targets
#

all:	strTest1 strTest2 strTest3 

strTest1:	strTest1.o $(OBJFILES)
	$(CC) $(CFLAGS) -o strTest1 strTest1.o $(OBJFILES) $(CLIBFLAGS)

strTest2:	strTest2.o $(OBJFILES)
	$(CC) $(CFLAGS) -o strTest2 strTest2.o $(OBJFILES) $(CLIBFLAGS)

strTest3:	strTest3.o $(OBJFILES)
	$(CC) $(CFLAGS) -o strTest3 strTest3.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

String.o:	String.h
strTest1.o:	String.h
strTest2.o:	String.h
strTest3.o:	String.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) strTest1.o strTest2.o strTest3.o core

realclean:        clean
	-/bin/rm -f strTest1 strTest2 strTest3 

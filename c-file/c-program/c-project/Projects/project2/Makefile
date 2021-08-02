#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sat Nov  7 04:51:03 2020
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

CFLAGS =	-ggdb -std=c99 -Wall -Wextra -pedantic
CLIBFLAGS =	-lm

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	mirsa_genkeys.c mirsa_lib.c mirsa_rw.c
PS_FILES =	
S_FILES =	
H_FILES =	mirsa_lib.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	mirsa_lib.o 

#
# Main targets
#

all:	mirsa_genkeys mirsa_rw 

mirsa_genkeys:	mirsa_genkeys.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mirsa_genkeys mirsa_genkeys.o $(OBJFILES) $(CLIBFLAGS)

mirsa_rw:	mirsa_rw.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mirsa_rw mirsa_rw.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

mirsa_genkeys.o:	mirsa_lib.h
mirsa_lib.o:	mirsa_lib.h
mirsa_rw.o:	mirsa_lib.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mirsa_genkeys.o mirsa_rw.o core

realclean:        clean
	-/bin/rm -f mirsa_genkeys mirsa_rw 

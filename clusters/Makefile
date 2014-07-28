#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: cluster

# To create the executable file count we need the object files
#
cluster:  cluster.o unionfind.o client.o
	$(CC) $(CFLAGS) -o cluster cluster.o unionfind.o client.o
	
# To create the object file, we need the source
#
cluster.o:  cluster.cpp
	$(CC) $(CFLAGS) -c cluster.cpp
	
# To create the object file, we need the source
#
unionfind.o:  unionfind.cpp
	$(CC) $(CFLAGS) -c unionfind.cpp

# To create the object file, we need the source files
#
client.o:  client.cpp
	$(CC) $(CFLAGS) -c client.cpp
	
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~

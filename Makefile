#Faaris Sattar
#fjs160130@utdallas.edu
#CS 3377.502

CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -lcurses -lcdk 

#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = prog6

OBJS = prog6.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

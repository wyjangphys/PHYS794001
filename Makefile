PROGRAM         = TTBarXSec
CC              = g++
LD              = g++
CXXFLAGS        = -g -O2 -I$(ROOTSYS)/include -std=c++11
LDFLAGS         = $(LIBS) $(GLIBS) -B/usr/X11R6/lib -B/usr/lib64 
OPT             =
ROOTLIBS        = $(shell root-config --libs)
ROOTGLIBS       = $(shell root-config --glibs)

SSBTREE_INPUTS   = ./analysis/SSBTree.C ./analysis/SSBTree.h

LIBS            = $(ROOTLIBS)
GLIBS           = $(ROOTGLIBS) -L/usr/X11R6/lib -lXext
OBJS            = CommonTools.o SSBTree.o TTBarXSec.o main.o
INPUTS	   	= $(MUONID_INPUTS) TTBarXSec.h TTBarXSec.cpp main.cpp

all: $(OBJS)													
	$(CC) $(OPT) $(LDFLAGS) -o $(PROGRAM) -g $(OBJS) $(LIBS)

main.o: main.cpp $(INPUTS) 
	$(CC) $(CXXFLAGS) -c main.cpp

SSBTree.o: $(SSBTREE_INPUTS)				
	$(CC) $(CXXFLAGS) -c ./analysis/SSBTree.C

TTBarXSec.o: TTBarXSec.h TTBarXSec.cpp
	$(CC) $(CXXFLAGS) -c ./TTBarXSec.cpp

CommonTools.o: CommonTools.h CommonTools.cpp
	$(CC) $(CXXFLAGS) -c CommonTools.cpp

clean:
	-rm -f *~ $(OBJS) core core.*	
	-rm -rf ti_files
	-rm -f $(PROGRAM)
	-rm -f *~;

distclean:						
	-rm -f *~ $(PROGRAM) $(OBJS)
	-rm -rf ti_files

run: $(PROGRAM) $(OBJS)	
	make all
	./$(PROGRAM) 1


# Welcomre to Mamat, 044101
#
# This is the project's Makefile. It contains the instructions for compiling
# the projects C files, and then link the generated objects into an executable.
# This simple file will compile "main.c" to "main.o" and then link it (with C
# runtime library) to the executable "prog.exe".
#
# To compile, open the terminal in the folder that contains
# this file and run "make".
#
# To clean, open the terminal in the folder that contains
# this file and run "make clean".
#
# All eclipse projects in this machine are under /home/mamat/Documents/

CXX = g++
CXX=g++
CXXLINK=$(CXX)
CXXFLAGS = -g -Wall -std=c++11
OBJS=string.o port.o ip.o 

firewall.exe: libfirewall.so libinput.so main.o $(OBJS)
		$(CXXLINK) -g -Wall $(OBJS) main.o -o firewall.exe -lfirewall -L. -linput

main.o: main.cpp string.h generic-field.h ip.h port.h input.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic main.cpp   

libfirewall.so: $(OBJS)
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so
	
string.o: string.cpp string.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic string.cpp
	
ip.o: ip.cpp string.h generic-field.h ip.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic ip.cpp
	
port.o: port.cpp string.h generic-field.h port.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic port.cpp
		
clean:
	rm -f *.o libfirewall.so


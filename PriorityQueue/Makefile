########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.





#Rule for .cpp files
# .SUFFIXES : .cpp.o 

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@




#Including
INCLUDES=  -I. 


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 


#ZEROTH PROGRAM
ALL_OBJ0=TestSearch.o
PROGRAM_0=TestSearch
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=TestDelete.o
PROGRAM_1=TestDelete
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)


#Compiling all

all: 	
		make $(PROGRAM_0)
		make $(PROGRAM_1)

run100s: 	
		./$(PROGRAM_0) 100_numbers.txt 100_test_search.txt

run100d:
		./$(PROGRAM_1) 100_numbers.txt 100_test_deletion.txt

run1000s: 
		./$(PROGRAM_0) 1000_numbers.txt 1000_test_search.txt

run1000d:
		./$(PROGRAM_1) 1000_numbers.txt 1000_test_deletion.txt


#Clean obj files

clean:
	(rm -f *.o; rm -f $(PROGRAM_0); rm -f $(PROGRAM_1))



(:

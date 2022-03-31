CXX = gcc
CXXFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2

labyrinth : arrays.o error_handling.o labyrinth.o main.o memory_managment.o my_string.o parse.o queue.o
			$(CXX) arrays.o error_handling.o labyrinth.o main.o memory_managment.o my_string.o parse.o queue.o -o labyrinth

error_handling.o : error_handling.c error_handling.h
	$(CXX) $(CXXFLAGS) -c error_handling.c

memory_managment.o : memory_managment.c memory_managment.h labyrinth.h arrays.h my_string.h queue.h error_handling.h
	$(CXX) $(CXXFLAGS) -c memory_managment.c

arrays.o : arrays.c arrays.h memory_managment.h labyrinth.h my_string.h queue.h
	$(CXX) $(CXXFLAGS) -c arrays.c

queue.o : queue.c queue.h arrays.h
	$(CXX) $(CXXFLAGS) -c queue.c

labyrinth.o : labyrinth.c labyrinth.h arrays.h my_string.h queue.h memory_managment.h
	$(CXX) $(CXXFLAGS) -c labyrinth.c 

parse.o : parse.c parse.h labyrinth.h arrays.h my_string.h queue.h
	$(CXX) $(CXXFLAGS) -c parse.c

main.o : main.c labyrinth.h arrays.h my_string.h queue.h parse.h
	$(CXX) $(CXXFLAGS) -c main.c

clean : 
	-rm *.o 
CFLAGS = -std=c++14 -g -fsanitize=address,undefined -Wall 

simulator: main.cpp event.o
	clang++ -o simulator $(CFLAGS) $^

event.o: Event.cpp Event.hpp 
	clang++ -c $(CFLAGS) $^

clean:
	rm *.o
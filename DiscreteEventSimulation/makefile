CFLAGS = -std=c++14 -fsanitize=address,undefined -Wall 

simulator: main.cpp customer.o attendant.o
	clang++ -o simulator $(CFLAGS) $^

attendant.o: Attendant.cpp Attendant.hpp customer.o
	clang++ -c $(CFLAGS) $^

customer.o: Customer.cpp Customer.hpp
	clang++ -c $(CFLAGS) $^

clean:
	rm *.o
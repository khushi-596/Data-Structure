all: isPal

isPal: stack.o palindrome.o
	g++ stack.o palindrome.o -o isPal

stack.o: stack.cpp stack.h
	g++ -c stack.cpp

palindrome.o: palindrome.cpp stack.h
	g++ -c palindrome.cpp

clean:
	rm -f *.o isPal

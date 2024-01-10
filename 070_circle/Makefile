CC = g++
CFLAGS = -std=c++98 -Wall -Werror -pedantic

circles: main.o circle.o point.o
	$(CC) $(CFLAGS) -o circles main.o circle.o point.o

main.o: main.cpp point.hpp circle.hpp
	$(CC) $(CFLAGS) -c main.cpp point.hpp circle.hpp

circle.o: circle.cpp circle.hpp
	$(CC) $(CFLAGS) -c circle.cpp circle.hpp

point.o: point.cpp point.hpp
	$(CC) $(CFLAGS) -c point.cpp point.hpp

clean:
	rm -rf *.o circles


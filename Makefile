.Phone: all clear run

all:main


main: main.o vector.o
	g++ $^ -o vector

%.o: %.cpp
	g++ $< -o $*.o -c

clear:
	rm -f *.o vector

run: main
	./vector 

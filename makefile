CC := g++
obj := main.o ohha.o
main: $(obj)
	$(CC) -o main $(obj) -std=c++14 -O2 -s
ohha.o: ohha.h ohha.cpp
	$(CC) -c ohha.cpp -std=c++14 -O2 -s
main.o: main.cpp
	$(CC) -c main.cpp -std=c++14 -O2 -s
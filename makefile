VHFlag = -include -std=c++17 # version and header flags

all: bin/program

bin/program: helpers lib/main.o
	@echo "linking to program"
	g++ lib/main.o lib/LinkedList.o -o bin/program

lib/main.o: src/main.cpp # the src/main.cpp makes it so that it would need to have a main.cpp file to work
	@echo "compiling main"
	g++ $(VFlag) -c src/main.cpp -o lib/main.o

helpers: lib/LinkedList.o

lib/LinkedList.o: src/LinkedList.cpp
	@echo "comliling LinkedList"
	g++ $(VFlag) -c src/LinkedList.cpp -o lib/LinkedList.o

clean: # doesn't allow the normal slashes
	@echo "removing .o and program files"
	-del lib\main.o lib\LinkedList.o
VHFlag = -include -std=c++17 # version and header flags

all: clean bin/program

program: bin/program

bin/program: helpers lib/main.o
	@echo "linking to program"
	g++ lib/main.o lib/Matris.o lib/Screen.o lib/LinkedList.o -o bin/program



lib/main.o: src/main.cpp # the src/main.cpp makes it so that it would need to have a main.cpp file to work
	@echo "compiling main"
	g++ $(VFlag) -c src/main.cpp -o lib/main.o

helpers: lib/Matris.o lib/LinkedList.o  lib/Screen.o



lib/LinkedList.o: src/LinkedList.cpp
	@echo "compiling LinkedList"
	g++ $(VFlag) -c src/LinkedList.cpp -o lib/LinkedList.o



lib/Matris.o: src/Matris.cpp
	@echo "compiling LinkedList"
	g++ $(VFlag) -c src/Matris.cpp -o lib/Matris.o



lib/Screen.o: src/Screen.cpp
	@echo "compiling Screen"
	g++ $(VFlag) -c src/Screen.cpp -o lib/Screen.o



clean: # doesn't allow the normal slashes
	@echo "removing .o and program files"
	-del lib\main.o lib\LinkedList.o
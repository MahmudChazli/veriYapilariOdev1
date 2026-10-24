VHFlag = -include -std=c++17 # version and header flags

all: bin/program

bin/program: lib/main.o
	@echo "linking to program"
	g++ ./lib/main.o -o ./bin/program

lib/main.o: src/main.cpp # the src/main.cpp makes it so that it would need to have a main.cpp file to work
	@echo "compiling main"
	g++ $(VFlag) -c ./src/main.cpp -o ./lib/main.o

clean: # doesn't allow the normal slashes
	@echo "removing .o and program files"
	-del lib\main.o bin\program.exe 
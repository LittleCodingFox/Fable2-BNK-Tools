all: clean lib

clean:
	rm -f *.o

lib: objects
	ar rcs ../../lib/libFragmentLib.a *.o
	rm -f *.o

objects:
	g++ -I../../Include/ -c ../../Source/*.cpp
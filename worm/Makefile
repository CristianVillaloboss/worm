
worm.x:  main.o getChar.o worm.o screen.o
	g++ -ggdb -o worm.x main.o getChar.o screen.o worm.o -lcurses -ltermcap

main.o: main.cpp
	g++ -c -ggdb main.cpp -o main.o

getChar.o: getChar.cpp 
	g++ -c -ggdb getChar.cpp -o getChar.o

screen.o: screen.cpp worm.hpp
	g++ -c -ggdb screen.cpp -o screen.o

worm.o: worm.cpp screen.hpp
	g++ -c -ggdb worm.cpp -o worm.o

clean:
	/bin/rm -f worm.x main.o getChar.o *~

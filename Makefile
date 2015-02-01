ann: Main.o Ann.o Node.o Parser.o
	g++ -pedantic -g -o ann Main.o Ann.o Node.o Parser.o
Parser.o: Parser.cpp Parser.h
	g++ -pedantic -g -c Parser.cpp
main.o: Main.cpp Ann.h
	g++ -pedantic -g -c Main.cpp
Ann.o: Ann.cpp Ann.h
	g++ -pedantic -g -c Ann.cpp
Node.o: Node.cpp Node.h
	g++ -pedantic -g -c Node.cpp
clean: 
	rm -f ann *.o

bin/main.exe: lib/matrix.o src/main.cpp
	g++ src/main.cpp lib/matrix.o -o bin/main.exe -I include

lib/matrix.o: src/_matrix.cpp
	g++ -c src/_matrix.cpp -o lib/matrix.o -I include
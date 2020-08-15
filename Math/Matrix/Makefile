bin/main.exe: lib/matrix.o src/main.cpp include/_matrix.hpp
	g++ src/main.cpp lib/matrix.o -o bin/main.exe -I include

lib/matrix.o: src/_matrix.cpp include/_matrix.hpp
	g++ -c src/_matrix.cpp -o lib/matrix.o -I include
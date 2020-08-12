bin/test.exe: lib/fractions.o src/test.cpp
	g++ src/test.cpp lib/fractions.o -o bin/test.exe -I include

lib/fractions.o: src/fractions.cpp
	g++ -c src/fractions.cpp -o lib/fractions.o -I include


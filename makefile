genres: genre.o helpers.o main.o movie.o
	g++ -o genres genre.o helpers.o main.o movie.o -g

main.o: helpers.h movie.h genre.h main.cpp
	g++ -c main.cpp -g

helpers.o: helpers.h helpers.cpp movie.h genre.h
	g++ -c helpers.cpp -g	

genre.o: genre.h genre.cpp movie.h
	g++ -c genre.cpp -g

movie.o: movie.h movie.cpp
	g++ -c movie.cpp -g

clean:
	rm *.o genres
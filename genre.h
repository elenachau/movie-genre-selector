#ifndef GENRE_H
#define GENRE_H

#include "movie.h"

class Genre{
    string genreOfObject;
    Movie moviesOfGenre[1000];
    int numMoviesInGenre;

    public:
        Genre();
        Genre(string, Movie*, int);
        Genre(const Genre&); //references a Genre object

        void setGenreOfObject(string);
        void addMovieToGenre(Movie);

        string getGenreOfObject();
        Movie* getMoviesofGenre();
        int getNumMoviesInGenre();
        void swapMovies(int, int);

        void displayMovies(); //add-on

};

#endif
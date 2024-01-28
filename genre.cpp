#include "genre.h"

Genre::Genre(){
    genreOfObject = "none";
    numMoviesInGenre = 0;
}

Genre::Genre(string g, Movie* m, int n){
    genreOfObject = g;
    numMoviesInGenre = n;
    for(int i = 0; i < n; i++){
        moviesOfGenre[i] = m[i];
    }

    // Genre::Genre(std::string genreOfObject, Movie* moviesOfGenre, int numMoviesInGenre){
    //     this->genreOfObject = genreOfObject; //"this" for clarity when same variable names exist
    //     for(int index = 0; index < numMoviesInGenre; index++){
    //         this->moviesOfGenre[index] = moviesOfGenre[index];
    //     }
    //     this->numMoviesInGenre = numMoviesInGenre;
    // }
}

Genre::Genre(const Genre& rhs){
    genreOfObject = rhs.genreOfObject;
    numMoviesInGenre = rhs.numMoviesInGenre;
    for(int i = 0; i < numMoviesInGenre; i++) {
        moviesOfGenre[i] = rhs.moviesOfGenre[i];
    }
}


void Genre::setGenreOfObject(string g){
    genreOfObject = g;
}

void Genre::addMovieToGenre(Movie m){
    moviesOfGenre[numMoviesInGenre] = m;
    numMoviesInGenre++;
}


string Genre::getGenreOfObject(){
    return genreOfObject;
}

Movie* Genre::getMoviesofGenre(){
    return moviesOfGenre;
}

int Genre::getNumMoviesInGenre(){
    return numMoviesInGenre;
}

void Genre::swapMovies(int i, int j){ //indices i and j
    Movie temp = moviesOfGenre[i];
    moviesOfGenre[i] = moviesOfGenre[j];
    moviesOfGenre[j] = temp;
}
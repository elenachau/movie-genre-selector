#include "movie.h"

Movie::Movie(){
    title = "none";
    director = "none";
    description = "none";
    actorCount = 0;
    genreCount = 0;
    year = 0;
    metaScore = 0;
    rating = 0.001;
}

Movie::Movie(string t, string d, string desc, string* a, string* g, int y, int meta, int ac, int gc, float rate) { //string* for an array of strings
    title = t;
    director = d;
    description = desc;
    actorCount = ac;
    genreCount = gc;
    year = y;
    metaScore = meta;
    rating = rate;

    for(int i = 0; i < actorCount; i++) {
        actors[i] = a[i];
    }
    for(int j = 0; j < genreCount; j++) {
        genres[j] = g[j];
    }
}


Movie::Movie(const Movie& rhs) { //reference to a Movie object
    title = rhs.title;
    director = rhs.director;
    description = rhs.description;
    actorCount = rhs.actorCount;
    genreCount = rhs.genreCount;
    year = rhs.year;
    metaScore = rhs.metaScore;
    rating = rhs.rating;

    for(int i = 0; i < actorCount; i++) {
        actors[i] = rhs.actors[i];
    }
    for(int j = 0; j < genreCount; j++) {
        genres[j] = rhs.genres[j];
    }
}

void Movie::setTitle(string t){
    title = t;
}

void Movie::setDirector(string d){
    director = d;
}

void Movie::setDescription(string desc){
    description = desc;
}

void Movie::addGenre(string genre) {
    genres[genreCount] = genre;

    //alt
    // if(genreCount < 500) {
    //     genres[genreCount] = genre;
    //     genreCount++;
    // }
    // else {
    //     cout << "Exceeded size of array." << endl;
    // }
}

void Movie::addActor(string actor) {
    if(actorCount < 5) {
        actors[actorCount] = actor;
        actorCount++;
    }
    else {
        cout << "Exceeded size of array." << endl;
    }
}

void Movie::setYear(int y) {
    year = y;
}

void Movie::setMetaScore(int ms) {
    metaScore = ms;
}
void Movie::setRating(float r) {
    rating = r;
}

string Movie::getTitle() {
    return title;
}

string Movie::getDirector() {
    return director;
}

string Movie::getDescription() {
    return description;
}

string* Movie::getActors() {
    return actors;
}

string* Movie::getGenres() {
    return genres;
}

int Movie::getYear() {
    return year;
}

int Movie::getMetaScore() {
    return metaScore;
}

int Movie::getActorCount() {
    return actorCount;
}

int Movie::getGenreCount() {
    return genreCount;
}

float Movie::getRating() {
    return rating;
}

void Movie::displayMovieData(){
    cout << title << endl;
    cout << "Director: " << director << endl;
    cout << "Actors: ";
    for(int i = 0; i < actorCount - 1; i++){
        cout << actors[i] << " * ";
    }
    cout << actors[actorCount - 1] << endl;
    cout << "Year: " << year << " Rating: " << rating << " Meta Score: " << metaScore << endl;
    cout << "Description: " << description << endl;
}
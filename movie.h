#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>

using namespace std;

class Movie{
    string title, director, description;
    string actors[100], genres[10];
    int year, metaScore, actorCount, genreCount;
    float rating;

    public:
        Movie();
        Movie(string, string, string, string*, string*, int, int, int, int, float);
        Movie(const Movie&);

        void setTitle(string);
        void setDirector(string);
        void setDescription(string);
        void addGenre(string);
        void setYear(int);
        void setMetaScore(int);
        void setRating(float);

        string getTitle();
        string getDirector();
        string getDescription();
        string* getActors();
        string* getGenres();
        int getYear();
        int getMetaScore();
        int getActorCount();
        int getGenreCount();
        float getRating();

};

#endif
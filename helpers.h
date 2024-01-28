#ifndef HELPERS_H
#define HELPERS_H

#include "genre.h"
#include <fstream>

int readCSV(Movie*, ifstream&);
void updateStringList(string, string*, int&);
void displayGenreMenu();
void displayMovieData(Movie m);
void displayMoviesOfGenreType(Genre);
Genre constructGenre(Movie*, int, string);
int getUserInput();
char getUserCharInput();
string performGenreSelection(int);
void bubbleSortSelection(int, Genre&);
void displaySortMenu(string);

#endif
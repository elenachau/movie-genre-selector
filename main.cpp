#include "helpers.h"
#include "genre.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Please provide a filename." << endl;
        return 1; //terminate with error
    }

    Movie movies[500];
    string fileName = argv[1];
    ifstream ifile(fileName);
    char cont;

    if(!ifile.is_open()) {
        cout << "File not found." << endl;
        return 2;
    }

    int numMovies = readCSV(movies, ifile);
    ifile.close();
    numMovies--;
    do{
        displayGenreMenu();
        int userChoice = getUserInput();
        if(userChoice == 9) {
            return 0;
        }

        string genreChosen = performGenreSelection(userChoice);
        Genre genreObj = constructGenre(movies, numMovies, genreChosen);
        displaySortMenu(genreObj.getGenreOfObject());
        int sortChoice = getUserInput();
        if(sortChoice == 6) {
            return 0;
        }
        bubbleSortSelection(sortChoice, genreObj);
        displayMoviesOfGenreType(genreObj);
        int movieChoice = getUserCharInput();
        if(movieChoice == genreObj.getNumMoviesInGenre()+1) {
            return 0;
        }
        displayMovieData(genreObj.getMoviesofGenre()[movieChoice-1]); //starting index 0
        cont = getUserCharInput();
    } while(cont != 'n' || cont != 'N');
    return 0;


}
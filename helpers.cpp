#include "helpers.h"

int readCSV(Movie* movies, ifstream& ifile){
    //1,Guardians of the Galaxy,"Action,Adventure,Sci-Fi",A group of intergalactic criminals are forced to work together to stop a fanatical warrior from taking control of the universe.,James Gunn,"Chris Pratt, Vin Diesel, Bradley Cooper, Zoe Saldana",2014,121,8.1,757074,333.13,76
    string dataRead, title, temp, genreString, description, director, actorString;
    int year, metaScore, actorCount = 0, genreCount = 0, numMovies = 0;
    float rating;

    while(ifile.good()){ //can read file
        string actors[100], genres[10];
        if(numMovies != 0) {
            getline(ifile, dataRead, ',');
            getline(ifile, title, ',');

            do{
                getline(ifile, genreString, ',');
                updateStringList(genreString, genres, genreCount);
            } while(genreString[genreString.size() - 1] != '/"');

            getline(ifile, description, ',');
            getline(ifile, director, ',');

            do{
                getline(ifile, actorString, ',');
                updateStringList(actorString, actors, actorCount);
            } while(actorString[actorString.size()-1] != '\"');

            getline(ifile, dataRead, ',');
            cout << dataRead << endl;
            year = stoi(dataRead); //str to int
            cout << dataRead << endl;
            getline(ifile, dataRead, ',');
            getline(ifile, dataRead, ',');
            rating = stof(dataRead); //str to float
            getline(ifile, dataRead, ',');
            getline(ifile, dataRead, ',');
            getline(ifile, dataRead);
            metaScore = stoi(dataRead);
            Movie newMovie(title, director, description, actors, genres, year, metaScore, actorCount, genreCount, rating);
            movies[numMovies-1] = newMovie; //starting index: 0
        }
        else{
            getline(ifile, dataRead);
        }
        actorCount = 0;
        genreCount = 0;
        numMovies++;
    } 
    return numMovies--;
}

void updateStringList(string newString, string* arr, int& count){
    if(newString[0] == '\"' || newString[0] == ' ') { //get rid of "" in movie title
        string temp = "";
        for(int i = 1; i < newString.size(); i++) {
            if(newString[i] != '\"') {
                temp+=newString[i];
            }
        }
        newString = temp;
    }
    else if(newString[newString.size()-1] == '\"') {
        string temp = "";
        for (int j = 0; j < newString.size()-1; j++) {
            temp+=newString[j];
        }
        newString = temp;
    }
    arr[count] = newString;
    count++;
}

void displayGenreMenu(){
    cout << "1. Sci-Fi" <<endl;
    cout << "2. Fantasy" <<endl;
    cout << "3. Biography" <<endl;
    cout << "4. Romance" <<endl;
    cout << "5. Comedy" <<endl;
    cout << "6. Horror" <<endl;
    cout << "7. Drama" <<endl;
    cout << "8. Family" <<endl;
    cout << "9. Exit" <<endl;
    cout<< "=======================================" <<endl;

    cout << "Which genre of movie would you like to view? ";
}

void displayMovieData(Movie m){
    cout << endl;
    cout << m.getTitle() << endl;
    cout << "Director: " << m.getDirector() << endl;
    cout << "Actors: ";
    for(int i = 0; i < m.getActorCount(); i++) {
        cout << m.getActors()[i];
        if(i != m.getActorCount()-1) { //prevents * at end of list if equal
            cout << " * "; //Chris Pratt * Vin Diesel * Bradley Cooper * Zoe Saldana
        }
    }
    cout << endl;
    cout << "Year: " << m.getYear() << " Rating: " << m.getRating() << " Meta Score: " << m.getMetaScore() << endl;
    cout << "Description: " << m.getDescription() << endl;
    cout << "Would you like to select another movie(y/n)?  " << endl;
}

void displayMoviesOfGenreType(Genre g, int sortType){
    cout << endl;
    for(int i = 0; i < g.getNumMoviesInGenre(); i++) {
        cout << i+1 << "." << g.getMoviesofGenre()[i].getTitle();
    }
    cout << g.getNumMoviesInGenre()+1 << ". Exit" << endl;
    cout << "======================" <<endl;
    cout << "Select a movie: ";
}

Genre constructGenre(Movie* movies, int numMovies, string genre){
    int num = 0;
    Movie genreMovies[250];

    for(int i = 0; i < numMovies; i++) {
        for(int j = 0; j < movies[i].getGenreCount(); j++) {
            if(movies[i].getGenres()[j] == genre) {
                genreMovies[num] = movies[i];
                num++;
            }
        }
    }
    Genre genreObj(genre, genreMovies, num);
    return genreObj;
}

int getUserInput(){
    int num;
    cin >> num;
    return num;
}

char getUserCharInput(){
    char val;
    cin >> val;
    return val;
}

string performGenreSelection(int c){
    switch(c){
        case 1: 
            return "Sci-Fi";
        case 2:
            return "Fantasy";
        case 3:
            return "Biography";
        case 4:
            return "Romance";
        case 5:
            return "Comedy";
        case 6: 
            return "Horror";
        case 7:
            return "Drama";
        case 8:
            return "Family";
    }
    return "error";
}

bool swapInt(int a, int b){
    if(a < b) {
        return false;
    }
    return true;
}

bool swapStrings(string a, string b){
    if(a < b) {
        return false;
    }
    return true;
}

bool swapFloats(float a, float b){
    if(a > b) { //sort ratings from greatest to lowest
        return false;
    }
    return true;
}

string getLast(string s) {
    bool spaceFound = false;
    string last = "";
    for(int i = 0; i < s.size(); i++) {
        if(spaceFound) {
            last += s[i];
        }
        if(s[i] == ' ' && !spaceFound){
            spaceFound = true;
        }
    }

    return last;
}

void bubbleSortSelection(int c, Genre& genre){
    bool doSwap;
    string directorILast, directorJLast;

    for(int i = 0; i < genre.getNumMoviesInGenre(); i++) {
        for(int j = i+1; j < genre.getNumMoviesInGenre(); j++) {
            switch(c) {
                case 1: //alphabetically by title
                    doSwap = swapStrings(genre.getMoviesofGenre()[i].getTitle(), genre.getMoviesofGenre()[j].getTitle());
                    break;
                case 2: //alphabetically by director last name
                    directorILast = getLast(genre.getMoviesofGenre()[i].getDirector());
                    directorJLast = getLast(genre.getMoviesofGenre()[j].getDirector());
                    doSwap = swapStrings(directorILast, directorJLast);
                    break;
                case 3: //numerically by year
                    doSwap = swapInt(genre.getMoviesofGenre()[i].getYear(), genre.getMoviesofGenre()[j].getYear());
                    break;
                case 4: //numerically by rating
                    doSwap = swapFloats(genre.getMoviesofGenre()[i].getRating(), genre.getMoviesofGenre()[j].getRating());
                    break;
                case 5: //numerically by metascore
                    doSwap = swapInt(genre.getMoviesofGenre()[i].getMetaScore(), genre.getMoviesofGenre()[j].getMetaScore());
                    if(doSwap) {
                        doSwap = false;
                    }
                    else {
                        doSwap = true;
                    }
                    break;
            }
            if(doSwap) {
                genre.swapMovies(i,j);
            }
        }
    }
}

void displaySortMenu(string genre){
    cout << endl;
    cout << "1. Alphabetically by title" << endl;
    cout << "2. Alphabetically by director last name" <<endl;
    cout << "3. Numerically by year" <<endl;
    cout << "4. Numerically by rating" << endl;
    cout << "5. Numerically by metascore" <<endl;
    cout << "6. Exit"<<endl;
    cout << "=======================================" <<endl;
    cout << "How would you like to view " << genre << " movies?";  

}


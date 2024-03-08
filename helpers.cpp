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
            } while(genreString[genreString.size() - 1] != '\"');

            getline(ifile, description, ',');
            getline(ifile, director, ',');

            do{
                getline(ifile, actorString, ',');
                updateStringList(actorString, actors, actorCount);
            } while(actorString[actorString.size()-1] != '\"');

            getline(ifile, dataRead, ',');
            year = stoi(dataRead); //str to int
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
            getline(ifile, dataRead); //skip column names
        }
        actorCount = 0;
        genreCount = 0;
        numMovies++;
    } 
    return numMovies;
}

//alt implementation of readCSV
int readFile(ifstream& file, Movie* movies) {
    int count = 0;

    string junk;
    getline(file, junk);

    while(!file.eof()) {
        getline(file, junk, ',');
        string title, genre, description, director, actor, yearStr, metascoreStr, ratingStr;
        string genreAr[5], actorAr[5];
        int genreCount = 0, actorCount = 0;

        getline(file, title, ',');
        getline(file, junk, '"');
        do{
            getline(file, genreAr[genreCount], ',');
            genreCount++;
        }while(genreAr[genreCount-1][genreAr[genreCount-1].length() - 1] != '"');
        genreAr[genreCount-1].pop_back();
        getline(file, description, ',');
        getline(file, director, ',');
        getline(file, junk, '"');
        do{
            getline(file, actorAr[actorCount], ',');
            actorCount++;
        }while(actorAr[actorCount-1][actorAr[actorCount-1].length() - 1] != '"');
        actorAr[actorCount-1].pop_back();
        getline(file, yearStr, ',');
        int year = stoi(yearStr);
        getline(file, junk, ',');
        getline(file, ratingStr, ',');
        float rating = stof(ratingStr);
        getline(file, junk, ',');
        getline(file, junk, ',');
        getline(file, metascoreStr, '\n');
        int metascore = stoi(metascoreStr);

        Movie temp(title, director, description, actorAr, genreAr, year, metascore, rating, actorCount, genreCount);
        movies[count] = temp;
        count++;
    }

    return count;
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
    cout << endl << "Would you like to select another movie(y/n)?  " << endl;
}

void displayMoviesOfGenreType(Genre g){
    cout << endl;
    for(int i = 0; i < g.getNumMoviesInGenre(); i++) {
        cout << i+1 << ". " << g.getMoviesofGenre()[i].getTitle() << endl;
    }
    cout << g.getNumMoviesInGenre()+1 << ". Exit" << endl;
    cout << "======================" <<endl;
    cout << "Select a movie: ";
}

Genre constructGenre(Movie* movies, int numMovies, string genre){ //copy of movies array address; copy constructor
    int num = 0;
    Movie genreMovies[500];

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
    

    // string extractLastName(string name) {
    //     size_t pog = fullName.find_last_of(' '); 
    //     //size_t is an unsigned int (non-negative including 0)
    //     //.find_last_of returns index of ' '
    //     if (pog != string::npos) { //std::string::npos means not found
    //         return fullName.substr(pog + 1); //.substr
    //     }
    //     else {
    //         return fullName;
    //     }
    // }

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

//alt method
// void bubbleSortSelection(int userChoice, Genre &genreObject){
//     int n = genreObject.getNumMoviesInGenre();
//     bool swapped;
//     switch(userChoice) {
//         case 1:
//             for(int i = 0; i < n-1; i++) {
//                 swapped = false;
//                 for(int j = 0; j < n-1-i; j++) {
//                     if(genreObject.getMoviesOfGenre()[j].getTitle() > genreObject.getMoviesOfGenre()[j+1].getTitle()) {
//                         genreObject.swapMovies(j, j+1);
//                         swapped = true;
//                     }
//                 }
//             }
//             break;
//         case 2: 
//             for(int i = 0; i < n-1; i++) {
//                 swapped = false;
//                 for(int j = 0; j < n-1-i; j++) {
//                     if(genreObject.getMoviesOfGenre()[j].getYear() > genreObject.getMoviesOfGenre()[j+1].getYear()) {
//                         genreObject.swapMovies(j, j+1);
//                         swapped = true;
//                     }
//                     else if(genreObject.getMoviesOfGenre()[j].getYear() == genreObject.getMoviesOfGenre()[j+1].getYear()) {
//                         if(genreObject.getMoviesOfGenre()[j].getTitle() > genreObject.getMoviesOfGenre()[j+1].getTitle()) {
//                             genreObject.swapMovies(j, j+1);
//                             swapped = true;
//                         }
//                     }
//                 }
//             }
//             break;
//         case 3:
//             for(int i = 0; i < n-1; i++) {
//                 swapped = false;
//                 for(int j = 0; j < n-1-i; j++) {
//                     if(genreObject.getMoviesOfGenre()[j].getRating() > genreObject.getMoviesOfGenre()[j+1].getRating()) {
//                         genreObject.swapMovies(j, j+1);
//                         swapped = true;
//                     }
//                     else if(genreObject.getMoviesOfGenre()[j].getRating() == genreObject.getMoviesOfGenre()[j+1].getRating()) {
//                         if(genreObject.getMoviesOfGenre()[j].getTitle() > genreObject.getMoviesOfGenre()[j+1].getTitle()) {
//                             genreObject.swapMovies(j, j+1);
//                             swapped = true;
//                         }
//                     }
//                 }
//             }
//             break;
//         default:
//             cout << "Invalid choice." << endl;
//             break;
//     }
// }

//combine alt/og method
// void bubbleSortSelection(int userChoice, Genre &genreObject){
//     int n = genreObject.getNumMoviesInGenre();
//     bool swapped = false;
//     for(int i = 0; i < genreObject.getNumMoviesInGenre(); i++) {
//         for(int j = i+1; j < genreObject.getNumMoviesInGenre(); j++) {
//             switch(userChoice){
//                 case 1: //alphabetical sort
//                     if(genreObject.getMoviesOfGenre()[i].getTitle() > genreObject.getMoviesOfGenre()[j].getTitle()){
//                         genreObject.swapMovies(i, j);
//                         swapped = true;
//                     }
//                     break;
//                 case 2: //year sort
//                     if(genreObject.getMoviesOfGenre()[i].getYear() > genreObject.getMoviesOfGenre()[j].getYear()){
//                         genreObject.swapMovies(i, j);
//                         swapped = true;
//                     }
//                     else if(genreObject.getMoviesOfGenre()[i].getYear() == genreObject.getMoviesOfGenre()[j].getYear()){
//                         if(genreObject.getMoviesOfGenre()[i].getTitle() > genreObject.getMoviesOfGenre()[j].getTitle()){
//                             genreObject.swapMovies(i, j);
//                             swapped = true;
//                         }
//                     }
//                     break;
//                 case 3: //rating sort
//                     if(genreObject.getMoviesOfGenre()[i].getRating() < genreObject.getMoviesOfGenre()[j].getRating()){
//                         genreObject.swapMovies(i, j);
//                         swapped = true;
//                     }
//                     else if(genreObject.getMoviesOfGenre()[i].getRating() == genreObject.getMoviesOfGenre()[j].getRating()){
//                         if(genreObject.getMoviesOfGenre()[i].getTitle() > genreObject.getMoviesOfGenre()[j].getTitle()){
//                             genreObject.swapMovies(i, j);
//                             swapped = true;
//                         }
//                     }
//                     break;
//                 default:
//                     cout << "Invalid choice. Select an option between 1-4";
//                     break;
//             }
//         }
//     }
// }

// void bubbleSortSelection(int userSortChoice, Genre& genreObject) {
//     Movie temp;
//     string A, B;
//     for(int i = 0; i < genreObject.getNumMoviesInGenre(); i++) {
//         for(int j = 0; j < genreObject.getNumMoviesInGenre(); j++){
//             switch(userSortChoice){
//                 case 1: //alphabetically by title
//                     if(genreObject.getMoviesOfGenre()[i].getTitle() < genreObject.getMoviesOfGenre()[j].getTitle()) { 
//                         temp = genreObject.getMoviesOfGenre()[i];
//                         genreObject.getMoviesOfGenre()[i] = genreObject.getMoviesOfGenre()[j];
//                         genreObject.getMoviesOfGenre()[j] = temp;
                        
//                     }
//                     break;
//                 case 2: //alphabetically by director last name
//                     A = genreObject.getMoviesOfGenre()[j].getDirector();
//                     A = extractLastName(A);
//                     A = toLowerCase(A);
//                     B = genreObject.getMoviesOfGenre()[j+1].getDirector();
//                     B = extractLastName(B);
//                     B = toLowerCase(B);
//                     if(A>B) { 
//                         temp = genreObject.getMoviesOfGenre()[j];
//                         genreObject.getMoviesOfGenre()[j]=genreObject.getMoviesOfGenre()[j+1];
//                         genreObject.getMoviesOfGenre()[j+1]=temp;
                        
//                     }
//                     break;
//                 case 3: //numerically by year, least to greatest
//                     if(genreObject.getMoviesOfGenre()[i].getYear()<genreObject.getMoviesOfGenre()[j].getYear()||(genreObject.getMoviesOfGenre()[i].getYear()==genreObject.getMoviesOfGenre()[j].getYear()&&(genreObject.getMoviesOfGenre()[i].getTitle()<genreObject.getMoviesOfGenre()[j].getTitle()))){ 
//                         temp = genreObject.getMoviesOfGenre()[i];
//                         genreObject.getMoviesOfGenre()[i] = genreObject.getMoviesOfGenre()[j];
//                         genreObject.getMoviesOfGenre()[j] = temp;
                        
//                     }
//                     break;
//                 case 4: //numerically by rating, greatest to least
//                     if(genreObject.getMoviesOfGenre()[j].getRating()<genreObject.getMoviesOfGenre()[j+1].getRating()||(genreObject.getMoviesOfGenre()[j].getRating()==genreObject.getMoviesOfGenre()[j+1].getRating()&&(genreObject.getMoviesOfGenre()[j].getTitle()>genreObject.getMoviesOfGenre()[j+1].getTitle()))){ 
//                         temp = genreObject.getMoviesOfGenre()[j];
//                         genreObject.getMoviesOfGenre()[j] = genreObject.getMoviesOfGenre()[j+1];
//                         genreObject.getMoviesOfGenre()[j+1] = temp;
//                     }
//                     break;
//                 case 5: //numerically by metaScore, greatest to least
//                     if(genreObject.getMoviesOfGenre()[j].getMetaScore()<genreObject.getMoviesOfGenre()[j+1].getMetaScore()||(genreObject.getMoviesOfGenre()[j].getMetaScore()==genreObject.getMoviesOfGenre()[j+1].getMetaScore()&&(genreObject.getMoviesOfGenre()[j].getTitle()>genreObject.getMoviesOfGenre()[j+1].getTitle()))){ 
//                         temp = genreObject.getMoviesOfGenre()[j];
//                         genreObject.getMoviesOfGenre()[j] = genreObject.getMoviesOfGenre()[j+1];
//                         genreObject.getMoviesOfGenre()[j+1] = temp;
//                     }
//                     break;
//                 default:
//                     displayInvalidInput();
//             }
//         }
//     }

// }

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


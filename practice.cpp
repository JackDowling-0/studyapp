/*
TO DO:
- handle card ID saving betweeen sessions
    -check for ID when reading a line




- single line conversion using pipe
- TTK counter

*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <conio.h>
#include <random>
#include <algorithm>

using namespace std;



//flashcard struct
struct Flashcard {
    string question;
    string answer;
    int cardID;
};

//define vectors
vector<Flashcard> flashcards;
vector<string> badLines;
vector<Flashcard> buffer;

//prototypes
int searchFile(string fileName);
int loadCardsFromLibrary();
void populateFromFile(string fileName);
void clearFile(string fileName);
void buildCard(string rawLine, int currID, bool fromLib);
void processCard(ifstream fileStream, int currID);
void populateFromFile(string fileName);
void listAllCards(const vector<Flashcard> &flashcards);
void displayCards(const vector<Flashcard> &flashcards, int cardRange);
bool isFileEmpty(string fileName);
void writeLibrary();
void bulkUpload();
void menuTree();

//check for a provided file (config, library, txtdump)
int searchFile(string fileName){
    string currentDirectory = ".";
    //search current directory return state
    for (const auto & entry : filesystem::directory_iterator(currentDirectory)) {
    if (entry.is_regular_file() && entry.path().filename() == fileName) {
        return true;
        break;
        } 
    }

    //return false AFTER for loop as search completes
    return false;
}

// load library on startup
int loadCardsFromLibrary(){
    int currID;
    string fileName = "library.txt";
    if (!searchFile(fileName)){
        //create a new save file
        ofstream newFile(fileName);
        newFile.close();
    }

    //Read cards into memory from library
    ifstream fileStream;
    fileStream.open(fileName);
    if (fileStream.is_open()){
        string rawLine;
        while (getline(fileStream, rawLine)) {
            bool fromLib = true;
            currID++;
            buildCard(rawLine, currID, fromLib);
        }
    } else {
        cerr << "Could not open library. (11)" << endl;
    }
    fileStream.close();

    //TO DO: get id of last flashcard in file
    return currID;
}

//function to clear textDump
void clearFile(string fileName) {
    ofstream fileStream(fileName, ofstream::out | ofstream::trunc);
    if (fileStream.is_open()) {
        fileStream.close();
        cout << "File cleared successfully." << endl;
    } else {
        cerr << "Failed to clear the file." << endl;
    }
}

//build a card from a single line
void buildCard(string rawLine, int currID, bool fromLib){
        if (!rawLine.empty() && rawLine.find(':') != string::npos) {

        string rawQuestion;
        string rawAnswer;


        if (fromLib == true) {
            int colonPos = rawLine.find(':');
            int startPos = rawLine.find_first_of(' ');
            rawQuestion = rawLine.substr(startPos, colonPos - 2);
            rawAnswer = rawLine.substr(colonPos + 1, EOF);

        } else {
            int colonPos = rawLine.find(':');
            rawQuestion = rawLine.substr(0, colonPos - 1);
            rawAnswer = rawLine.substr(colonPos + 1);

            rawQuestion.erase(0, rawQuestion.find_first_not_of(' '));
            rawQuestion.erase(rawQuestion.find_last_not_of(' ') + 1);
            rawAnswer.erase(0, rawAnswer.find_first_not_of(' '));
            rawAnswer.erase(rawAnswer.find_last_not_of(' ') + 1);
        }

        Flashcard newFlashcard;
        newFlashcard.question = rawQuestion;
        newFlashcard.answer = rawAnswer;
        newFlashcard.cardID = currID;

        flashcards.push_back(newFlashcard);
        } 
        else if (rawLine.find(":") == string::npos && !rawLine.empty()) {
        badLines.push_back(rawLine);
        }
}

void processCard(ifstream fileStream, int currID, bool fromLib){
    string rawLine;
    while (getline(fileStream, rawLine)) {
        buildCard(rawLine, currID, fromLib);
    }
}

//populate flashcards into memory
void populateFromFile(string fileName){
    //open given file and populate flashcard vector from file contents
    ifstream fileStream(fileName);
    int currID;
    fileStream.open(fileName);
    if (fileStream.is_open()) {
        string rawLine;

        while (getline(fileStream, rawLine)) {
            bool fromLib = false;
            buildCard(rawLine, currID, fromLib);
    }
    } else {
        cout << "Could not open the file." << endl;
    }
    fileStream.close();
}

//
void listAllCards(const vector<Flashcard> &flashcards) {
    if (!flashcards.empty()) {
        for (const auto &card : flashcards) {
            cout << card.cardID << ". " << card.question << endl;
            cout << "Answer: " << card.answer << endl;
            cout << endl;
        }
    } else {
        cout << "No flashcards found." << endl;
    }
    
}

void displayCards(const vector<Flashcard> &flashcards, int cardRange) {
    vector<int> usedCards;
    int rMax = flashcards.size();

    //begin main loop
    for (int i = 0; i < cardRange; i++) {
        int ptr = rand() % rMax;
        system("cls");
        cout << "Test";
        cout << ptr << endl;


        //check to see if we've used the card before
        //if we have, then increment the pointer until we haven't
        while (find(usedCards.begin(), usedCards.end(), ptr) == usedCards.end()) {
            ptr++;
            if (find(usedCards.begin(), usedCards.end(), ptr) == usedCards.end()) {
                usedCards.push_back(ptr);
                break;
            }
        } 

        //if we haven't, then store the cardID and print the card
        usedCards.push_back(ptr);
        cout << flashcards[ptr].cardID << ". " << "Question: " << flashcards[ptr].question << endl;
        getch();
        cout << flashcards[ptr].answer << endl;   

        if (getch() == 'e'){
            break;
        }

    }

}

bool isFileEmpty(string fileName){
    ifstream inFile(fileName);

    if (inFile.peek() == ifstream::traits_type::eof()) {
        return true;
    } else {
        return false;
    }
}

//write to library from bulk upload
void writeLibrary(){

    ofstream library;
    library.open("library.txt", ios_base::app);

    if (library.is_open()){
        for (const auto &card : flashcards){
            library << card.cardID << ". " << card.question << ": " << card.answer << endl; 
        }
    } else {
        cerr << "Unable to open file." << endl;
    }
}

// enables bulk upload from a text dump file
void bulkUpload() {
    //search for dump file
    string currentDirectory = ".";
    string fileName = "textDump.txt";

    if (isFileEmpty(fileName) || !searchFile(fileName)) {
        ofstream textDump("textDump.txt");
        textDump.close();

        system("start textDump.txt");
        
        system("pause");
        textDump.close();

        populateFromFile(fileName);
    }
    //write to library
    writeLibrary();

    //clear buffer file
    clearFile("textDump.txt");
}

void menuTree() {
    //root menu
    cout << "Welcome to simpleNote. Please select an option: " << endl;
    cout << "1. Study from library." << endl;
    cout << "2. Add to library." << endl;
    cout << "3. Exit program." << endl;

    //init input, range
    int input;
    int cardRange;
    cin >> input;

    switch (input) {
        case 1: 
            cout << "Select a display option: " << endl;
            cout << "1. List all cards" << endl;
            cout << "2. List random cards" << endl;
            //TO DO: work through cards in order
            cin.ignore();
            cin >> input;

            switch (input) {
                case 1:
                listAllCards(flashcards);
                
                cout << "What would you like to do?" << endl;
                cout << "1. Inspect a card." << endl;
                cout << "2. Study from a range." << endl;
                cout << "3. Add a card." << endl;
                cin.ignore();
                cin >> input;
                switch(input) {
                    case 1:
                        //prompt user to inspect a card
                        int pickCard;
                        cout << "\nType a number to inspect a card (or 0 to exit): ";
                        cin >> pickCard;

                        //output the card based on vector placement
                        cout << pickCard << ". " << flashcards[pickCard - 1].question << endl;
                        cout << flashcards[pickCard - 1].answer << endl;

                        cout << "What would you like to do?" << endl;
                        cout << "1. Edit this card." << endl;
                        cout << "2. Delete this card." << endl;
                        cout << "3. Go back." << endl;

                        cin.ignore();
                        cin >> input;
                        switch (input) {
                            case 1:  //TO DO EDIT
                                cout << "EDITING STILL UNDER DEVELOPMENT" << endl;
                            case 2: //TODO DELETE
                                cout << "DELETING STILL UNDER DEVELOPMENT" << endl;
                            case 3: 
                                break;

                        }
                }
                
                case 2:
                cout << "How many cards would you like to study?: ";
                cin.ignore();
                cin >> cardRange;
                displayCards(flashcards, cardRange);

                default:
                    cout << "Please input a valid response." << endl;
            }
        case 2:
            cout << "Select how you'd like to add cards: " << endl;
            cout << "1. In bulk" << endl;
            cout << "2. As a line" << endl;
            cout << "3. As Q-A" << endl;
            cin.ignore();
            cin >> input;
            switch (input) {
                case 1: 
                    bulkUpload();
                default:
                    cout << "Please input a valid response." << endl;
            }
        default:
            cout << "Please input a valid response." << endl;
    }
}

int main() {
    loadCardsFromLibrary();

    menuTree();

    return 0;
}

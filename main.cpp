//TODO - 1. Create lamda functions
    //    a. verify if out of bounds
    //    b. display card question
    //    c. display card answer

#include <iostream>
#include <vector>
#include <conio.h>

#include "flashcards.h"

int main(){


    Flash::Flashcard flashcard;


    //generate 10 flash cards
    for (int i = 0; i <= 10; i++) {
        flashcard.Create(i, "someQuestion", "someAnswer");
    }

    flashcard.DisplayCards();

    std::cout << "\n";

    for (int i = 0; i <= 10; i = i + 2) {
        flashcard.UpdateCard(i, "someotherText", "someTest", true);
    }

    std::cout <<"\n";
    
    getch();

    return 0;
}

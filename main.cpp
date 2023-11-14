//TODO - 1. Create lamda functions
    //    a. verify if out of bounds
    //    b. display card question
    //    c. display card answer

#include <iostream>
#include <vector>

#include "flashcards.h"

int main(){

    std::vector<Flash::Flashcard> library;

    Flash::Flashcard flashcard;


    //generate 10 flash cards
    for (size_t i = 1; i <= 10; i++) {
        flashcard.Create(i, "someQuestion", "someAnswer");
    }


    flashcard.DisplayCards();

    //delete card 6...
    flashcard.Destroy(6);
    flashcard.Destroy(3);
    flashcard.Destroy(3);

    std::cout << "\n Destroying card 6... \n" << std::endl;

    //we should have 9 cards now...
    flashcard.DisplayCards();
    
    return 0;
}
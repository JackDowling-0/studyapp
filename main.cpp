#include "lib.h"

int main(){
    Flash::FlashcardManager manager;
    Flash::Parser parser(manager);

    std::vector<Flash::Flashcard> cards;
    for (int i = 0; i < 5; i++){
        cards.emplace_back(Flash::Flashcard(i, "This is a", "Flash card"));
    }

    manager.addFlashcards(cards);

    // manager.readFromStorage();

    // manager.displayCards();

    return 0;
}

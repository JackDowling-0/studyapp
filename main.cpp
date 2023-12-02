#include "lib.h"

// int init(){
//     Flash::FlashcardManager manager;
//     Flash::Parser parser(manager);
    
//     loadMenus();
//     manager.readFromStorage();

// }

int main(){

    Flash::FlashcardManager manager;
    Flash::Parser parser(manager);

    manager.readFromStorage();
    manager.displayCards();

    manager.addFlashcard(Flash::nextID, "this is a test", "and it worked");

    std::vector<Flash::Flashcard> vecBffr = manager.convertCards(manager.flashcards);
    manager.writeLibraryToStorage(vecBffr);



    

    return 0;
}

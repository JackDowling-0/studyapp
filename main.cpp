#include "lib.h"

int main(){
    Flash::FlashcardManager manager;
    Flash::Parser parser;
    
    std::string l1 = "This is a :line of text";
    std::string l2 = "        This is a :line of text";
    std::string l3 = "    This is a :   line of text     ";

    manager.addFlashcard(parser.parseLine(l1));
    manager.addFlashcard(parser.parseLine(l2));
    manager.addFlashcard(parser.parseLine(l3));

    manager.displayCards();

    return 0;
}

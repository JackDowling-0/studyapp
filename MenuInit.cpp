#include "lib.h"

namespace Flash{

void Init(Flash::FlashcardManager& manager, Flash::Parser& parser, Menu& mainMenu, Menu*& currMenu){


    currMenu->addMenu(Menu("create", "Create Flashcard", currMenu));
    currMenu->addMenu(Menu("view", "View Flashcards", currMenu));
    currMenu->addMenu(Menu("practice", "Practice Flashcards", currMenu));

    //move to Menu -> menus (1/3) // currMenu = mainMenu.menus[0]
    currMenu = &currMenu->menus[0];
    
    //add function options to create menu
    
    /*"CREATE" FUNCTIONS*/
    //BULK UPLOAD
    currMenu->addAction({"bulkUpload",
        "Create a set of cards by uploading a file.",
            std::function<void(std::string)>([&manager, &parser](std::string){
                //function logic

                //TODO: prompt user and open bin/dump.txt


                //TODO: check that dump.txt is saved and closed then process
                parser.parseFile("bin/dump.txt");
                //TODO: display cards that were created
                //TODO: display failed cards and ask if user wants to validate them // if not, go back to prevMenu(mainMenu)
            })});

    //LINE UPLOAD //TODO: request input
    currMenu->addAction({"lineUpload",
        "Create a set of cards by providing a line.",
            std::function<void(std::string)>([&manager, &parser](std::string s){
                //function logic
                parser.parseLine(s);

                int it = manager.flashcards.size();
                manager.displayCard(manager.flashcards.at(it));

                //TODO: prompt to add another // if no, go back to main menu
            })});

    //FLASHCARD BUILDER
    currMenu->addAction({"creator",
        "Create a set of cards with the creation wizard.",
            std::function<void(std::string)>([&manager, &parser](std::string){
                //function logic


            })});
    
        //Initialize submenus for "create"


    //"VIEW" MENU
    currMenu = &mainMenu.menus[1];

        //initialize subMenus

        //single menu
        currMenu->addMenu(Menu("single", "Inspect a flashcard", currMenu));
        currMenu = &currMenu->menus[0];

        currMenu->addMenu(Menu("edit", "Edit this flashcard.", currMenu->getPrevMenu()));

    //"PRACTICE" MENU
    currMenu = &mainMenu.menus[2];

        //initialize subMenus
        currMenu->addMenu(Menu("rotate", "Rotate through cards", currMenu));
        currMenu->addMenu(Menu("multi", "Select multiple cards to practice.", currMenu));
        currMenu->addMenu(Menu("range", "Practice from a range of cards.", currMenu));





}
}
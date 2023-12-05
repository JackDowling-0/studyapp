#include "lib.h"

void INIT_MENU(){
    Flash::FlashcardManager manager;
    Flash::Parser parser(manager);

    Menu mainMenu;

    Menu* currMenu = &mainMenu;

    currMenu->addMenu(Menu("create", "Create Flashcard", currMenu));
    currMenu->addMenu(Menu("view", "View Flashcards", currMenu));
    currMenu->addMenu(Menu("practice", "Practice Flashcards", currMenu));

    //move to Menu -> menus (1/3) // currMenu = mainMenu.menus[0]
    currMenu = &currMenu->menus[0];
    currMenu->displayMenu();
    
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
    currMenu->displayMenu();

        //initialize subMenus

        currMenu->addMenu(Menu("single", "Inspect a flashcard", currMenu));
        currMenu = &currMenu->menus[0];

        currMenu->displayMenu();

    // //"PRACTICE" MENU
    // currMenu = &mainMenu.menus[2];
    // currMenu->displayMenu();

    currMenu = currMenu->getPrevMenu();
    currMenu->displayMenu();


}
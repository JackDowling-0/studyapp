#include "lib.h"

// //add function options to create menu
//     currMenu->addAction({"name",
//     "description",
//         std::function<void(std::string)>([&manager, &parser](std::string s = ""){
//             //function logic

//         })});

namespace Flash{

FlashcardManager manager;
Parser parser(manager);

Menu mainMenu;

Menu* currMenu = &mainMenu;

bool isValidInput(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

void Init(Flash::FlashcardManager& manager, Flash::Parser& parser, Menu& mainMenu, Menu*& currMenu){

    //grab library
    manager.readFromStorage();

    currMenu->addMenu(Menu("create", "Create Flashcard", currMenu));
    currMenu->addMenu(Menu("view", "View Flashcards", currMenu));
    currMenu->addMenu(Menu("practice", "Practice Flashcards", currMenu));

    //move to Menu -> menus (1/3) // currMenu = mainMenu.menus[0]
    currMenu = &currMenu->menus[0];
    
    /*"CREATE" FUNCTIONS*/
    //BULK UPLOAD
    currMenu->addAction({"bulkUpload",
        "Create a set of cards by uploading a file.",
            std::function<void(std::string)>([&manager, &parser](std::string s = ""){
                //function logic

                std::cout << "Reading from file...\n";

                parser.bulkUpload();
            })});

    //LINE UPLOAD
    currMenu->addAction({"lineUpload",
        "Create a set of cards by providing a line.",
            std::function<void(std::string)>([&manager, &parser, &currMenu, &mainMenu](std::string s){
                //function logic


                std::string str = "init";
                //start loop to take in lines
                while (true){
                    std::getline(std::cin, str);

                    if (str == ""){
                        break;
                    }

                    // Parse the given line and place the card on the stack
                    manager.addFlashcard(parser.parseLine(str));
                } 

                //return to main menu
                currMenu = &mainMenu;

            })});

    //FLASHCARD BUILDER
    currMenu->addAction({"creator",
        "Create a set of cards with the creation wizard.",
            std::function<void(std::string)>([&manager, &parser, &currMenu, &mainMenu](std::string){
                //function logic

                //start main input loop, break if input is ever empty
                while (true){
                    //get question, answer
                    std::string q, a;
                    
                    std::cout << "Input a question: \n";
                    std::getline(std::cin, q);

                    std::cout << "Input an answer: \n";
                    std::getline(std::cin, a);

                    if (q == "" || a == ""){
                        break;
                    }

                    //load onto temporary flashcard
                    manager.addFlashcard(nextID, q, a);
                }

                //send back to main menu
                currMenu = &mainMenu;


            })});
    
        //Initialize submenus for "create"


    //"VIEW" MENU
    currMenu = &mainMenu.menus[1];

    //init edit menu
    currMenu->addMenu(Menu("edit", "Edit this flashcard.", currMenu->getPrevMenu()));

    /*FUNCTIONS*/

    // display and inspect
    currMenu->addAction({"displayAll",
    "Display all cards with IDs",
        std::function<void(std::string)>([&manager, &parser, &currMenu](std::string s = ""){
            //function logic

            std::string str;
            int i = 0;
            //display all flashcards (this is manager.displayCards() but reformatted)
            for (const auto& card : manager.flashcards){
                std::cout << card.second.getInfo().ID << ": " << card.second.getInfo().question << "\n";
                std::cout << "      " << card.second.getInfo().answer << std::endl;
            }

            while (str != "back" && str != "edit" && str != "exit") {
                std::cout << "Input a card number to inspect (or 'back' to return to the main menu): ";
                std::cin >> str;

                if (isValidInput(str)) {
                    i = std::stoi(str);

                    if (manager.flashcards.count(i)) {
                        manager.displayCard(i);
                    } else {
                        std::cout << "Error! Card " << i << " not found!\n";
                    }
                } else if (str == "exit"){
                    exit(0);
                } else if (str == "edit"){
                    //enter edit menu
                    currMenu = &currMenu->menus.at(0);
                }
            }
        })});

    //"PRACTICE" MENU
    currMenu = &mainMenu.menus[2];

        //initialize subMenus -> add function

        currMenu->addAction({"rotate",
        "Rotate through all cards",
            std::function<void(std::string)>([&manager, &parser, &currMenu, &mainMenu](std::string s = ""){
                //function logic

                std::cout << "Press any key to continue, 'q' to quit back to main menu." << std::endl;
                for (const auto& card : manager.flashcards){
                    std::cout << "(" << card.first << ") " << card.second.getInfo().question;
                    char c = getch();
                    if (c == 'q'){
                        break;
                    }
                    fflush(stdin);


                    std::cout << "      " << card.second.getInfo().answer << "\n";
                    c = getch();
                    if (c == 'q'){
                        break;
                    }
                    fflush(stdin);
                }
                currMenu = &mainMenu;


            })});

        currMenu->addMenu(Menu("multi", "Select multiple cards to practice.", currMenu));
        currMenu->addMenu(Menu("range", "Practice from a range of cards.", currMenu));

    currMenu = &mainMenu;

}
}
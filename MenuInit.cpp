#include "lib.h"

// //function template
// currMenu->addAction({"name",
// "description",
//     std::function<void(std::string)>([&manager, &parser](std::string s = ""){
//         //function logic

//     })});

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
                    if (q == "q"){return;}

                    std::cout << "Input an answer: \n";
                    std::getline(std::cin, a);
                    if (a == "q"){return;}

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
                    if (manager.practiceCard(card.first) == 1){break;}
                }
                currMenu = &mainMenu;


            })});

        currMenu->addAction({"multiSelect",
        "Select from a set of flashcards to practice",
            std::function<void(std::string)>([&manager, &parser](std::string s = ""){
                //function logic
                std::string input;
                getline(std::cin, input);
                std::stringstream ss(input);

                std::vector<std::string> v;
                std::vector<int> practiceBffr;
                
                //seperate given line into digits and push them into a temporary vector
                while (getline(ss, s, ' ')) {
                    v.push_back(s);
                }

                //iterate over string, converting it to a number and pushing valid ones into another vector
                for (const auto& str : v){
                    //prevent stoi exceptions
                    bool skip = false;
                    for (const auto& ltr : str){
                        if (!isdigit(ltr)){ skip = true; break;}
                    }
                    if (!skip){
                        practiceBffr.push_back(stoi(str));
                    }
                }

                //keep looping over cards until told to stop
                while (true){
                    for (const auto& str : practiceBffr){
                        if (manager.flashcards.count(str)){
                            //return back to main if we receive signal 1(q pressed)
                            if (manager.practiceCard(manager.flashcards.at(str).getInfo().ID) == 1) {return;}
                        }
                    }
                }

            })});

        currMenu->addAction({"rangeSelect",
        "Select from a range of flashcards to practice",
            std::function<void(std::string)>([&manager, &parser, &currMenu, &mainMenu](std::string s = ""){
                //function logic
                std::string min, max;

                //loop until user provides us with a valid range or presses q

                [&]{
                    loop:
                while (true){

                    std::cout << "Enter lower range: ";
                    getline(std::cin, min);
                    if (min.empty()){ continue;} else if (min == "q"){return;}

                    std::cout << "Enter upper range: ";
                    getline(std::cin, max);
                    if (max.empty()){ continue;} else if (max == "q"){return;}
                    std::cout << max;

                    for (const char& c : min){
                        if (!isdigit(c)){
                            if (c == 'q'){return;}
                            std::cout << "Invalid input. Please provide a number and a range. \n";
                            continue;
                        }
                    }
                    break;
                }

                while (true){
                    std::vector<int> nums = {stoi(min), stoi(max)};
                    
                    for (const int& num : nums){
                        //see if either of our numbers are out of range
                        if (!manager.flashcards.count(nums[0]) || !manager.flashcards.count(nums[1])){
                            std::cout << "Cards out of range. Please try again.\n";
                            goto loop;
                        }
                        if (manager.practiceCard(num) == 1) {return;}
                    }
                }
                }();
                
            currMenu = &mainMenu;
            })});

        currMenu->addMenu(Menu("range", "Practice from a range of cards.", currMenu));

    currMenu = &mainMenu;

}
}
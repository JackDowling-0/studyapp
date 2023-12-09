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

    //Init options for main menu
    currMenu->addAction({"create",
    "Create and add flashcards",
        std::function<void(std::string)>([&](std::string s = ""){
            //function logic
            currMenu = &currMenu->menus[0];
        })});

    currMenu->addAction({"view",
    "View and edit flashcards",
        std::function<void(std::string)>([&](std::string s = ""){
            //function logic
            std::string str;
            int i = 0;

            //display all flashcards (this is manager.displayCards() but reformatted)
            for (const auto& card : manager.flashcards){
                std::cout << card.second.getInfo().ID << ": " << card.second.getInfo().question << "\n";
                std::cout << "      " << card.second.getInfo().answer << std::endl;
            }
            getch();
        })});

    currMenu->addAction({"practice",
    "Practice your flashcards",
        std::function<void(std::string)>([&](std::string s = ""){
            //function logic
            currMenu = &currMenu->menus[2];
        })});

    //move to Menu -> menus (1/3) // currMenu = mainMenu.menus[0]
    currMenu = &currMenu->menus[0];
    
    /*"CREATE" FUNCTIONS*/
    //BULK UPLOAD
    currMenu->addAction({"batch",
        "Create a set of cards by uploading a file.",
            std::function<void(std::string)>([&](std::string s = ""){
                //function logic

                std::cout << "Reading from file...\n";

                parser.bulkUpload();
            })});

    //LINE UPLOAD
    currMenu->addAction({"line",
        "Create a set of cards by providing a line.",
            std::function<void(std::string)>([&](std::string s){
                //function logic

                std::cout << "Enter a line that you'd like to parse into a flashcard: \n    ";


                std::string str = "init";
                //start loop to take in lines
                while (true){
                    std::getline(std::cin, str);

                    if (str == ""){
                        break;
                    }

                    // Parse the given line and place the card on the stack
                    Flashcard card = parser.parseLine(str);
                    if (card.getInfo().ID == -1){
                        continue;
                    } else {
                        manager.addFlashcard(card);
                    }
                } 

                //write library to storage
                manager.writeLibraryToStorage();

                //return to main menu
                currMenu = &mainMenu;

            })});

    //FLASHCARD BUILDER
    currMenu->addAction({"creator",
        "Create a set of cards with the creation wizard.",
            std::function<void(std::string)>([&](std::string){
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

                    //load flashcard into memory
                    manager.addFlashcard(nextID, q, a);
                }

                //write library to storage
                manager.writeLibraryToStorage();

                //send back to main menu
                currMenu = &mainMenu;


            })});


    //"VIEW" MENU
    //move to Menu -> menus (2/3) // currMenu = mainMenu.menus[1]
    currMenu = &mainMenu.menus[1];

    //init edit menu
    // currMenu->addMenu(Menu("edit", "Edit a flashcard.", currMenu->getPrevMenu()));


    //"PRACTICE" MENU
    //move to Menu -> menus (3/3) // currMenu = mainMenu.menus[2]
    currMenu = &mainMenu.menus[2];

        //initialize subMenus -> add function

        currMenu->addAction({"rotate",
        "Rotate through all cards",
            std::function<void(std::string)>([&](std::string s = ""){
                //function logic

                while (true){
                    std::cout << "Press any key to continue, 'q' to quit back to main menu." << std::endl;
                    for (const auto& card : manager.flashcards){
                        if (manager.practiceCard(card.first) == 1){currMenu = &mainMenu; return;}
                    }
                }

            })});

        currMenu->addAction({"multi",
        "Select from a set of flashcards to practice",
            std::function<void(std::string)>([&](std::string s = ""){
                std::cout << "Enter the ID of the flashcards you'd like to review, separated by spaces: ";
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
                    std::cout << "\n'q' to quit" << std::endl;
                    for (const auto& str : practiceBffr){
                        if (manager.flashcards.count(str)){
                            if (manager.practiceCard(manager.flashcards.at(str).getInfo().ID) == 1) {return;}
                        }
                    }
                }

            })});

        currMenu->addAction({"range",
        "Select from a range of flashcards to practice",
            std::function<void(std::string)>([&](std::string s = ""){
                //function logic
                std::string min, max;

                //loop until user provides us with a valid range or presses q
                [&]{
                    loop:
                while (true){

                    std::cout << "Enter lower range: " << std::endl;
                    getline(std::cin, min);
                    if (min.empty()){ continue;} else if (min == "q"){return;}

                    std::cout << "Enter upper range: " << std::endl;
                    getline(std::cin, max);
                    if (max.empty()){ continue;} else if (max == "q"){return;}

                    for (const char& c : min){
                        if (!isdigit(c)){
                            if (c == 'q'){return;}
                            std::cout << "Invalid input. Please provide a number and a range." << std::endl;
                            continue;
                        }
                    }
                    break;
                }

                while (true){
                    std::vector<int> nums = {stoi(min), stoi(max)};
                    
                    for (int i = nums[0]; i <= nums[1]; i++){
                        //see if either of our numbers are out of range
                        if (!manager.flashcards.count(i)){
                            std::cout << "Cards out of range. Please try again.\n";
                            goto loop;
                        }
                        if (manager.practiceCard(i) == 1) {return;}
                    }
                }
                }();
                
            currMenu = &mainMenu;
            })});

        currMenu->addMenu(Menu("range", "Practice from a range of cards.", currMenu));

    currMenu = &mainMenu;

}
}
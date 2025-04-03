#include "head/parser.h"
#include "head/flashcardmanager.h"
#include "head/menus.h"
#include "head/utility.h"

void const MainMenu(){

    FlashcardManager* flashcardManager = FlashcardManager::getInstance();
    
    Menu create("Create a Flashcard", {"Upload a File", "Enter a Line", "Creation Wizard"});

    flashcardManager->readFromStorage();

    //initialize the menu and enter into first input loop
    //we will just return out of all subsequent submenus
    Menu mainMenu("Main Menu", {"View", "Practice", "Create", "Delete", "Exit"});
    while(true){
        clear_screen();

        mainMenu.displayMenu();

        size_t input = 0;
        std::cin >> input;
        std::string delNum;
        switch(input){
            case 1:
                flashcardManager->displayAllCards();
                getc(stdin);
                break;
            case 2:
                PracticeMenu();
                break;
            case 3:
                CreateMenu();
                break;
            case 4:
                flashcardManager->displayAllCards();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                std::getline(std::cin, delNum);
                if (delNum == "\n"){
                    break;
                } else {
                    if (flashcardManager->removeFlashcard(stoull(delNum) - 1)) {
                        flashcardManager->writeLibraryToStorage();
                    }
                    break;
                }
            case 5:
                std::cout << "Exiting..." << std::endl;
                return;
            default:
                std::cout << "Invalid input. Please select a valid option." << std::endl;
        }
    }
}

void const PracticeMenu(){
    Menu practiceMenu("Practice Flashcards", {"Rotate", "Select", "Shuffle", "Range", "Back to Main Menu", "Exit"});

    practiceMenu.displayMenu();
    size_t input = 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    while(true){
        clear_screen();
        practiceMenu.displayMenu();

        std::cin >> input;
        
        switch(input){
            case 1:
                FlashcardManager::getInstance()->rotateThroughCards();
                break;
            case 2:
                FlashcardManager::getInstance()->selectedPractice();
                break;
            case 3:
                FlashcardManager::getInstance()->shuffleCards();
                break;
            case 4:
                FlashcardManager::getInstance()->rangeSelect();
                break;
            case 5:
                std::cout << "Returning to Main Menu..." << std::endl;
                return;
            case 6:
                std::cout << "Exiting..." << std::endl;
                exit(1);
            default:
                std::cout << "Invalid input." << std::endl;
                continue;
        }
    }
}

void const CreateMenu(){

    Menu createMenu("Create or Upload a Flashcard", {"Batch Upload", "Line Upload", "Prompt Wizard", "Back to Main Menu", "Exit"});

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    size_t input = 0;
    while (true){
        clear_screen();
        createMenu.displayMenu();

        std::cin >> input;

        switch(input){
            case 1:
                bulkUpload();
                break;
            case 2:
                startLineUpload();
                break;
            case 3:
                promptWizard();
                break;
            case 4:
                return;
            case 5:
                exit_program();
                exit(0);
            default:
                std::cout << "Invalid input." << std::endl;
                continue;
        }
    }

    return;
}

void const exit_program(){
    FlashcardManager::getInstance()->writeLibraryToStorage();
    FlashcardManager::getInstance()->displayAllCards();
    return;
}

void startLineUpload(){
    
    clear_screen();

    std::cout << "Enter a colon-separated line that you'd like to parse into a flashcard (Enter to exit): \n\n";
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    while (true){
        std::getline(std::cin, input);

        if (input == ""){ 
            return; 
        }

        Flashcard card = parseLine(input, ':');
        if (card.getAnswer() != "" && card.getAnswer() != ""){
            FlashcardManager::getInstance()->addFlashcard(card);
            FlashcardManager::getInstance()->writeLibraryToStorage();
        }
    }

    return;
}

void const promptWizard(){
    std::cout << "Enter a question and answer pair below to create a flashcard\nPress enter on an empty line to return." <<std::endl;

    std::string question;
    std::string answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    while(true){
        clear_screen();

        std::cout << "Enter a question: " << std::endl;
        std::getline(std::cin, question);
        if (question == "") { 
            FlashcardManager::getInstance()->writeLibraryToStorage();
            return;
        }

        std::cout << "Enter an answer: " << std::endl;
        std::getline(std::cin, answer);
        if (answer == "") { 
            FlashcardManager::getInstance()->writeLibraryToStorage();
            return;
        }

        FlashcardManager::getInstance()->addFlashcard(FlashcardManager::getInstance()->getNextID(), question, answer);
    }
    return;
}

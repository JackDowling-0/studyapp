#include "head/menus.h"
#include "head/flashcardmanager.h"

#include <iostream>
#include <limits>

void const MainMenu(){

    FlashcardManager* flashcardManager = FlashcardManager::getInstance();
    
    Menu create("Create a Flashcard", {"Upload a File", "Enter a Line", "Creation Wizard"});
    //create some flashcards for testing
    flashcardManager->addFlashcard(0, "Is this a card?", "Yes it is.");
    flashcardManager->addFlashcard(1, "Is this also a card?", "No it is not.");
    flashcardManager->addFlashcard(2, "This is definitely a card.", "Sure, why not.");

    //initialize the menu and enter into input loop
    Menu mainMenu("Main Menu", {"View", "Practice", "Create", "Delete", "Exit"});
    while(true){
        system("cls");

        mainMenu.displayMenu();

        size_t input = 0;
        std::cin >> input;
        std::string delNum;
        switch(input){
            case 1:
                flashcardManager->displayAllCards();
                getch();
                break;
            case 2:
                PracticeMenu();
                break;
            case 3:
                CreateMenu();
                break;
            case 4:
                flashcardManager->displayAllCards();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

                std::getline(std::cin, delNum);
                if (delNum == "\n"){
                    break;
                } else {
                    flashcardManager->removeFlashcard(stoull(delNum) - 1);
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
    while(true){
        system("cls");
        practiceMenu.displayMenu();

        std::cin >> input;
        
        switch(input){
            case 1:
                FlashcardManager::getInstance()->rotateThroughCards();
                break;
            case 2:
                FlashcardManager::getInstance()->selectedPractice();
            case 3:
                FlashcardManager::getInstance()->shuffleCards();
            case 4:
                FlashcardManager::getInstance()->rangeSelect();
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






    return;
}
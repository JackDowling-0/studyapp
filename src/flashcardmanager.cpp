#include "head/flashcardmanager.h"

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <limits>
#include <random>

FlashcardManager* FlashcardManager::instance = nullptr;

FlashcardManager* flashcardManager = FlashcardManager::getInstance();

//construct and add flashcards to the stack
void FlashcardManager::addFlashcard(size_t ID, std::string question, std::string answer){
    flashcards.emplace_back(ID, question, answer);
}
void FlashcardManager::addFlashcard(const Flashcard& flashcard) {
    flashcards.emplace_back(flashcard);
}

//update all IDs
void FlashcardManager::updateIDs(){
    std::sort(flashcards.begin(), flashcards.end());
}

//display specified flashcard
void FlashcardManager::displayCard(const size_t& cardNumber){

    std::cout << "Card ID: " << flashcards[cardNumber].getID() + 1<< "." << std::endl;
    std::cout << "Question: " << flashcards[cardNumber].getQuestion() << std::endl;
    std::cout << "Answer: " << flashcards[cardNumber].getAnswer() << std::endl;
}

// //overload to print based on the full card, not just the number
// void displayCard(const Flashcard& flashcard);

//display all flashcards
void FlashcardManager::displayAllCards() {
    for (size_t i = 0; i < flashcards.size(); ++i){
        displayCard(i);

        std::cout << std::endl;
    }
}

//remove a flashcard
bool FlashcardManager::removeFlashcard(const size_t& cardNumber){
    if (cardNumber < flashcards.size()) {
        flashcards.erase(flashcards.begin() + cardNumber);
        return true;
    } else {
        std::cerr << "Invalid card number: " << cardNumber << std::endl;
        return false;
    }
}

//add card to storage
void appendCardToStorage(const Flashcard& flashcard){
    
}

//write all flashcards in memory to long-term storage
void writeLibraryToStorage();

//read all flashcards in long-term storage to memory
void readFromStorage();

//practice card
void FlashcardManager::practiceCard(const size_t& cardNumber){
    system("cls");
    Flashcard& card = flashcards[cardNumber];

    //display the question
    std::cout << card.getQuestion() << std::endl;

    getch();
    //display the answer
    std::cout << "  " << card.getAnswer() << std::endl;

    getch();
}
void FlashcardManager::practiceCard(const Flashcard& card){
    system("cls");

    //display the question
    std::cout << card.getQuestion() << std::endl;

    getch();
    //display the answer
    std::cout << "  " << card.getAnswer() << std::endl;
    getch();
}

void FlashcardManager::rotateThroughCards(){

    for (const auto& card : flashcards){
        practiceCard(card);
    }

    while (true){
        std::string input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        std::cout << "\nContinue? (y/n): ";
        std::getline(std::cin, input);

        if (!input.empty() && !(input == "n") && !(input == "N")){
            for (const auto& card : flashcards){
                practiceCard(card);
            }
        } else {
            break;
        }
    }
    return;
}

//ways to practice
void FlashcardManager::selectedPractice(){
    std::vector<size_t> selectedCards;
    displayAllCards();

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    //prompt until user exits
    while (true){
        std::cout << "Enter card number (press Enter to finish): ";
        std::getline(std::cin, input);
        if (!input.empty()){
            selectedCards.emplace_back(stoull(input) - 1);
        } else {
            break;
        }
    }
    //sort the array so we skip duplicate cards
    std::sort(selectedCards.begin(), selectedCards.end());

    practiceSelectedCards(selectedCards);
    while (true){
        std::cout << "\nContinue? (y/n): ";
        std::getline(std::cin, input);
        if (!input.empty() && !(input == "n") && !(input == "N")){
            practiceSelectedCards(selectedCards);
        } else {
            break;
        }
    }
}

void FlashcardManager::practiceSelectedCards(const std::vector<size_t>& selectedCards){
    system("cls");
    size_t currCard, prevCard;

    for (const auto& it : selectedCards){
        currCard = it;
        if (currCard == prevCard){
            continue;
        }
        practiceCard(currCard);
        prevCard = currCard;
    }
}
void FlashcardManager::shuffleCards(){
    std::vector<size_t> randomFlashcards;

    //populate new vector with cardNumbers
    for (size_t i = 0; i < flashcards.size(); ++i){
        randomFlashcards.emplace_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(randomFlashcards.begin(), randomFlashcards.end(), g);

    for (size_t i = 0; i < randomFlashcards.size(); ++i){
        practiceCard(randomFlashcards[i]);
    }
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    while (true){
        system("cls");

        std::cout << "\nContinue? (y/n): ";
        std::getline(std::cin, input);
        if (!input.empty() && !(input == "n") && !(input == "N")){
            std::shuffle(randomFlashcards.begin(), randomFlashcards.end(), g);
            for (size_t i = 0; i < randomFlashcards.size(); ++i){
                practiceCard(randomFlashcards[i]);
            }
        } else {
            break;
        }
    }
}
void FlashcardManager::rangeSelect(){
    system("cls");
    displayAllCards();

    size_t start;
    size_t end;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    //get range
    std::cout << "Start: ";
    std::cin >> start;
    if (start < 0){
        std::cout << "Invalid input" << std::endl;
        return;
    }
    std::cout << "End: ";

    std::cin >> end;
    start -= 1;
    end -= 1;
    if (end > flashcards.size() || end <= start){
        std::cout << "Invalid input" << std::endl;
        return;
    }

    for (size_t i = start; i <= end; ++i){
        practiceCard(i);
    }

    std::string input;
    while (true){
        system("cls");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        std::cout << "\nContinue? (y/n): ";
        std::getline(std::cin, input);
        if (!input.empty() && !(input == "n") && !(input == "N")){
            for (size_t i = start; i <= end; ++i){
                practiceCard(i);
            }
        } else {
            break;
        }
    }
}

//get nextID from manager
size_t getNextID();
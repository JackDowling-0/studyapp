#include "flashcardmanager.h"

FlashcardManager* FlashcardManager::instance = nullptr;

FlashcardManager* flashcardManager = FlashcardManager::getInstance();

void FlashcardManager::addFlashcard(std::string& question, std::string& answer){
    flashcards.emplace_back(Flashcard{question, answer});
    ++nextID;
}
void FlashcardManager::addFlashcard(const Flashcard& flashcard) {
    flashcards.emplace_back(flashcard);
    ++nextID;
}

void FlashcardManager::displayCard(size_t cardNumber){
    std::cout << "Card ID: " << cardNumber + 1 << "." << std::endl;
    std::cout << "Question: " << flashcards[cardNumber].question << std::endl;
    std::cout << "Answer: " << flashcards[cardNumber].answer << std::endl;
}


void FlashcardManager::displayAllCards() {
    for (size_t i = 0; i < flashcards.size(); ++i){
        displayCard(i);

        std::cout << std::endl;
    }
}

bool FlashcardManager::removeFlashcard(size_t cardNumber){
    if (cardNumber < flashcards.size()) {
        flashcards.erase(flashcards.begin() + cardNumber);
        return true;
    } else {
        std::cerr << "Invalid card number: " << cardNumber << std::endl;
        return false;
    }
}

//todo: pull from array
void FlashcardManager::appendCardToStorage(const Flashcard& flashcard){
    std::ofstream library("library.txt", std::ios_base::app);

    library << "Question: " << flashcard.question << std::endl;
    library << "Answer: " << flashcard.answer << std::endl;
    
    library.close();
}

//todo: pull from array
void FlashcardManager::writeLibraryToStorage(){

    std::ofstream library("library.txt", std::ios::out);

    for (size_t i = 0; i < flashcards.size(); ++i){
        library << "ID: " << i << std::endl;
        library << "Question: " << flashcards[i].question << std::endl;
        library << "Answer: " << flashcards[i].answer << std::endl;
    }
    library.close();
}

void FlashcardManager::readFromStorage(){
    std::ifstream library("library.txt");
    std::ifstream dump("dump.txt");
    //first time setup
    if (!library || !dump){
        if (!dump){
            std::ofstream dump("dump.txt");
            dump.close();
        }
        std::ofstream library("library.txt");
        library.close();
        return;
    }

    std::string q = "";
    std::string a = "";
    std::string line;
    int counter = 0;
    Flashcard card;
    while (std::getline(library, line)){
        if (counter == 0){
            nextID = stoull(line.substr(4));
            counter++;
            continue;
        } else if (counter == 1){
            q = line.substr(10);
            counter++;
            continue;
        } else if (counter == 2){
            a = line.substr(8);
            counter = 0;
            addFlashcard(q, a);
            continue;
        }
    }
    
    library.close();
}

void FlashcardManager::practiceCard(size_t cardNumber){
    system("cls");
    Flashcard& card = flashcards[cardNumber];

    //display the question
    std::cout << card.question << std::endl;

    getch();
    //display the answer
    std::cout << "  " << card.answer << std::endl;

    getch();
}
void FlashcardManager::practiceCard(const Flashcard& card){
    system("cls");

    std::cout << card.question << std::endl;

    getch();
    std::cout << "  " << card.answer << std::endl;
    getch();
}

void FlashcardManager::rotateThroughCards(){
    system("cls");
    for (const auto& card : flashcards){
        practiceCard(card);
    }

    while (true){
        std::string input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
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
    system("cls");
    std::vector<size_t> selectedCards;
    displayAllCards();

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    while (true){
        std::cout << "Enter the card numbers you'd like to press, one at a time (press Enter to finish): ";
        std::getline(std::cin, input);
        if (!input.empty()){
            selectedCards.emplace_back(stoull(input) - 1);
        } else {
            break;
        }
    }

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
    size_t currCard = 0;
    size_t prevCard = 0;

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
    system("cls");
    std::vector<size_t> randomFlashcards;

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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    //get range
    std::cout << "Start: ";
    std::cin >> start;
    if (std::cin.fail() || start > INT16_MAX){
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

    char input = 0;
    while (true){
        system("cls");

        std::cout << "\nContinue? (y/n): ";

        input = std::getchar();
        if (input | (0x20 != 'y')){
            break;
        }
        for (size_t i = start; i <= end; ++i){
            practiceCard(i);
        }
    }
}

size_t FlashcardManager::getNextID(){
    return FlashcardManager::getInstance()->nextID;
}
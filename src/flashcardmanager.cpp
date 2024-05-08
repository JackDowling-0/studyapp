#include "head/flashcardmanager.h"

FlashcardManager* FlashcardManager::instance = nullptr;

FlashcardManager* flashcardManager = FlashcardManager::getInstance();

void FlashcardManager::addFlashcard(size_t ID, std::string question, std::string answer){
    flashcards.emplace_back(ID, question, answer);
    ++nextID;
}
void FlashcardManager::addFlashcard(const Flashcard& flashcard) {
    flashcards.emplace_back(flashcard);
    ++nextID;
}


void FlashcardManager::updateIDs(){
    std::sort(flashcards.begin(), flashcards.end());
}

void FlashcardManager::displayCard(const size_t& cardNumber){

    std::cout << "Card ID: " << flashcards[cardNumber].getID() + 1<< "." << std::endl;
    std::cout << "Question: " << flashcards[cardNumber].getQuestion() << std::endl;
    std::cout << "Answer: " << flashcards[cardNumber].getAnswer() << std::endl;
}


void FlashcardManager::displayAllCards() {
    for (size_t i = 0; i < flashcards.size(); ++i){
        displayCard(i);

        std::cout << std::endl;
    }
}

bool FlashcardManager::removeFlashcard(const size_t& cardNumber){
    if (cardNumber < flashcards.size()) {
        flashcards.erase(flashcards.begin() + cardNumber);
        for (size_t i = cardNumber; i < flashcards.size(); ++i){
            flashcards[i].updateID(i);
        }
        FlashcardManager::getInstance()->nextID -= 1;
        return true;
    } else {
        std::cerr << "Invalid card number: " << cardNumber << std::endl;
        return false;
    }
}

void FlashcardManager::appendCardToStorage(const Flashcard& flashcard){
    std::ofstream library("library.txt", std::ios_base::app);

    library << "ID: " << flashcard.getID() << std::endl;
    library << "Question: " << flashcard.getQuestion() << std::endl;
    library << "Answer: " << flashcard.getAnswer() << std::endl;
    
    library.close();
}

void FlashcardManager::writeLibraryToStorage(){

    std::ofstream library("library.txt", std::ios::out);

    for (const auto& it : flashcards){
        library << "ID: " << it.getID() << std::endl;
        library << "Question: " << it.getQuestion() << std::endl;
        library << "Answer: " << it.getAnswer() << std::endl;
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

    size_t d;
    std::string q = "";
    std::string a = "";
    std::string line;
    int counter = 0;
    Flashcard card;
    while (std::getline(library, line)){
        if (counter == 0){
            d = stoull(line.substr(4));
            counter++;
            continue;
        } else if (counter == 1){
            q = line.substr(10);
            counter++;
            continue;
        } else if (counter == 2){
            a = line.substr(8);
            counter = 0;
            addFlashcard(nextID, q, a);
            continue;
        }
    }
    
    library.close();
}

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

    std::cout << card.getQuestion() << std::endl;

    getch();
    std::cout << "  " << card.getAnswer() << std::endl;
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

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

size_t FlashcardManager::getNextID(){
    return FlashcardManager::getInstance()->nextID;
}
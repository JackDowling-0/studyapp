#ifndef FLASHCARDMANAGER_H
#define FLASHCARDMANAGER_H

#include <string>
#include <vector>

class Flashcard {
    public:
    //default constructor
    Flashcard(size_t id = 0, std::string question = "", std::string answer = "") : ID(id), question(question), answer(answer){}

    //update the current flashcard's ID
    void updateID(const size_t& num);

    size_t getID() const { return ID; }
    std::string getQuestion() const { return question; }
    std::string getAnswer() const {return answer; }

    bool operator<(const Flashcard& other) const{
        return ID < other.ID;
    }
    private:

        size_t ID;
        std::string question;
        std::string answer;

}; // end flashcard

class FlashcardManager {
    private:
        static FlashcardManager* instance;
        std::vector<Flashcard> flashcards;
        FlashcardManager() {};
        size_t nextID;

    public:
        //constructor
        FlashcardManager(const FlashcardManager&) = delete;
        FlashcardManager& operator=(const FlashcardManager&) = delete;

        static FlashcardManager* getInstance() {
            if (!instance){
                instance = new FlashcardManager();
            }
            return instance;
        }

        //construct and add flashcards to the stack
        void addFlashcard(size_t ID, std::string question, std::string answer);
        void addFlashcard(const Flashcard& card);

        //update all IDs
        void updateIDs();

        //display specified flashcard
        void displayCard(const size_t& cardNumber);
        void displayCard(const Flashcard& flashcard);

        //display all flashcards
        void displayAllCards();

        //remove a flashcard
        bool removeFlashcard(const size_t& cardNumber);

        //add card to storage
        void appendCardToStorage(const Flashcard& flashcard);

        //write all flashcards in memory to long-term storage
        void writeLibraryToStorage();

        //read all flashcards in long-term storage to memory
        void readFromStorage();

        //practice card
        void practiceCard(const size_t& cardNumber);
        void practiceCard(const Flashcard& card);

        //ways to practice
        void rotateThroughCards();
        void selectedPractice();
        void practiceSelectedCards(const std::vector<size_t>& selectedCards);
        void shuffleCards();
        void rangeSelect();
        
        //grab structured flashcard data
        void getFlashcardData();

        //get nextID from manager
        size_t const getNextID();



}; //end flashcardmanager

#endif
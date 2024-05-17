#ifndef FLASHCARDMANAGER_H
#define FLASHCARDMANAGER_H

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <limits>
#include <random>
#include <string>
#include <fstream>

struct Flashcard {
    std::string question;
    std::string answer;
};

class FlashcardManager {
    private:
        //singleton
        static FlashcardManager* instance;
        std::vector<Flashcard> flashcards;
        FlashcardManager() {};
        size_t nextID = 0;

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

        void setNextID(size_t num){
            nextID = num;
        }

        //construct and add flashcards to the stack
        void addFlashcard(std::string& question, std::string& answer);
        void addFlashcard(const Flashcard& card);

        //update all IDs
        void updateIDs();

        //display specified flashcard
        void displayCard(size_t cardNumber);
        void displayCard(const Flashcard& flashcard);

        //display all flashcards
        void displayAllCards();

        //remove a flashcard
        bool removeFlashcard(size_t cardNumber);

        //add card to storage
        void appendCardToStorage(const Flashcard& flashcard);

        //write all flashcards in memory to long-term storage
        void writeLibraryToStorage();

        //read all flashcards in long-term storage to memory
        void readFromStorage();

        //practice card
        void practiceCard(size_t cardNumber);
        void practiceCard(const Flashcard& card);

        //ways to practice
        void rotateThroughCards();
        void selectedPractice();
        void practiceSelectedCards(const std::vector<size_t>& selectedCards);
        void shuffleCards();
        void rangeSelect();

        //get nextID from manager
        size_t getNextID();



}; //end flashcardmanager

#endif
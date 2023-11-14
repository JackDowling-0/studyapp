#ifndef FLASHCARDS_H
#define FLASHCARDS_H


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace Flash 
{
    //TODO - 2. Create public ID (what card are we currently looking at)
    // flashcard type
    class Flashcard
    {

        private:
        // Attributes
            int ID;

            std::string question;
            std::string answer;
        
        
        // Methods
            void updateID(int startingIndex) {
                int i = startingIndex + 1;
                for (auto it = library.begin() + startingIndex; it != library.end(); it++) {
                    it->ID = i;
                    i++;
                }
            }
        
        // Public attributes
        public:
            // public library to hold all flashcards currently in memory
            std::vector<Flashcard> library;

            void Create(int num, std::string quest, std::string ans) 
            {
                Flashcard flashcard;

                flashcard.ID = num;
                flashcard.question = quest;
                flashcard.answer = ans;

                library.push_back(flashcard);
            }
        
            void DisplayCards() {
                std::cout << "Printing flashcards...\n";

                for (const auto card : library) {
                    std::cout << "Card ID: " << card.ID << "." << std::endl;
                    std::cout << "Question: " << card.question << std::endl;
                    std::cout << "Answer: " << card.answer << std::endl;
                }
            }


            void Destroy(int cardNumber) {
                //TO DO: CREATE ANONYMOUS FUNCTION
                if (cardNumber < 1 || cardNumber > library.size()) {
                    std::cout << "Error! Card number out of bounds!" << std::endl;

                } else {
                    auto it = library.begin() + cardNumber;
                    library.erase(it);

                    int startingIndex = cardNumber;
                    updateID(startingIndex);
                }
            }

            void DisplayCard(const int cardNumber) {

                    // Check if card number indexes us out of bounds
                    if (cardNumber < 0 || cardNumber > library.size()) {
                        std::cout << "Error! Flashcard not found!" << std::endl;

                    } else {
                        // Create an iterator based on ID number
                        const auto &card = library.at(cardNumber);

                        // Check to see if we've deleted the flashcard
                        if (card.ID == '\0') {
                            std::cout << "Error! Flashcard not found!" << std::endl;

                        } else {
                            // Print flashcard with elements
                            std::cout << "Printing flashcard...\n";

                            std::cout << "Card ID: " << card.ID << "." << std::endl;
                            std::cout << "Question: " << card.question << std::endl;
                            std::cout << "Answer: " << card.answer << std::endl;
                        }
                    }
            }
            //TODO - 3. Create update functions of class Flashcard
    };
}

#endif
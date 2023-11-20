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

	public:
		//library to hold flash cards
		std::vector<Flashcard> library;

        private:
        // Attributes
            int ID;

            std::string question;
            std::string answer;
        
        
        // Methods
            void updateID(int startingIndex) {
                int i = startingIndex;
                for (auto it = library.begin() + startingIndex; it != library.end(); it++) {
                    it->ID = i;
                    i++;
                }
            }
        
        // Public attributes
        public:

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
                if (cardNumber < 0 || cardNumber > library.size()) {
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

                        // Print flashcard with elements
                        std::cout << "Printing flashcard...\n";

                        std::cout << "Card ID: " << card.ID << "." << std::endl;
                        std::cout << "Question: " << card.question << std::endl;
                        std::cout << "Answer: " << card.answer << std::endl;
                        }
            }

	    void UpdateCard(int cardNumber, std::string newQuestion = "//EMPTY//", std::string newAnswer = "//EMPTY//", bool print = false){

		    if (cardNumber < 0 || cardNumber > library.size()) {

			    std::cout << "Error! Flashcard not found!" << std::endl;

            } else if (newQuestion == "//EMPTY//" && newAnswer == "//EMPTY//") {
            
                std::cout << "Error! Must provide either question or answer!" << std::endl;    

            } else {

                //create an iterator
                auto &card = library.at(cardNumber);

                if (newQuestion != "") {
                    card.question = newQuestion;
                }

                if (newAnswer != "") {
                    card.answer = newAnswer;
                }

                if (print != false) {
                    DisplayCard(cardNumber);
                }

	    	}
	    }
    };
}

#endif

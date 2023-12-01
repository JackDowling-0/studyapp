#ifndef TESTING_H
#define TESTING_H

#include "flashcards.h"

class Test {

    public:

        class ParserTest{
            public:
                struct FlashcardResult {
                FlashcardResult(std::pair<int, int> idScore = {},
                                std::pair<int, std::pair<std::string, std::string>> questionScore = {}, 
                                std::pair<int, std::pair<std::string, std::string>> answerScore = {}) {}

                std::pair<int, std::pair<int, int>> idScore;
                std::pair<int, std::pair<std::string, std::string>> questionScore;
                std::pair<int, std::pair<std::string, std::string>> answerScore;
                };


                FlashcardResult testInfo(Flash::Flashcard::FlashcardInfo info, Flash::Flashcard::FlashcardInfo expectedInfo){
                    FlashcardResult result;
                    int testResult = 0;
                    
                    std::cout << "ID... \n";
                    //test ID
                    if (info.ID == expectedInfo.ID){
                        result.idScore.first = 1;
                        testResult++;
                        std::cout << "OK \n \n";
                    } else {
                        std::cout << "No Match! \n";
                        std::cout << "  ..." << info.ID<< "\n";
                        std::cout << "  ..." << expectedInfo.ID << "\n \n";
                    }
                    result.idScore.second.first = info.ID;
                    result.idScore.second.second = expectedInfo.ID; 

                    //test question
                    std::cout <<"Question... \n";
                    if (info.question == expectedInfo.question){
                        result.questionScore.first = 1;
                        testResult++;
                        std::cout << "OK \n \n";
                    } else {
                        std::cout << "No Match! \n";
                        std::cout << "  ..." << info.question << "\n";
                        std::cout << "  ..." << expectedInfo.question << "\n \n";
                    } 
                    result.questionScore.second.first = expectedInfo.question;
                    result.questionScore.second.second = info.question;

                    //test answer
                    std::cout << "Answer... \n";
                    if (info.answer == expectedInfo.answer){
                        result.answerScore.first = 1;
                        std::cout << "OK \n \n";
                        testResult++;
                    } else {
                        std::cout << "No Match! \n";
                        std::cout << "  ..." << info.answer << "\n";
                        std::cout << "  ..." << expectedInfo.answer << "\n \n";
                    }
                    result.answerScore.second.first = info.ID;
                    result.answerScore.second.second = expectedInfo.ID;

                    std::cout << "Score: " << testResult << " out of 3.";
                    std::cout << "\n--------------------------------------------------\n";
                    std::cout << "--------------------------------------------------" << std::endl;
                    return result;
                }

                void SingleBuildTest(){
                    Flash::FlashcardManager manager;
                    Flash::Parser parser;

                    //Create comparison objects
                    Flash::Flashcard::FlashcardInfo expectedInfoCard1 = Flash::Flashcard::FlashcardInfo(0, "This is a", "line of text");
                    Flash::Flashcard::FlashcardInfo expectedInfoCard2 = Flash::Flashcard::FlashcardInfo(1, "This is a", "line of text");
                    Flash::Flashcard::FlashcardInfo expectedInfoCard3 = Flash::Flashcard::FlashcardInfo(2, "This is a", "line of text");

                    //Set of lines to test
                    std::string l1 = "This is a :line of text";
                    std::string l2 = "        This is a :line of text";
                    std::string l3 = "    This is a :   line of text     ";

                    //Create card objects to test from lines of parsing the test lines
                    Flash::Flashcard::FlashcardInfo info1 = parser.parseLine(l1).getInfo();
                    Flash::nextID++;
                    Flash::Flashcard::FlashcardInfo info2 = parser.parseLine(l2).getInfo();
                    Flash::nextID++;
                    Flash::Flashcard::FlashcardInfo info3 = parser.parseLine(l3).getInfo();

                    //Retrieve test results from card objects
                    FlashcardResult card1Result = testInfo(info1, expectedInfoCard1);
                    FlashcardResult card2Result = testInfo(info2, expectedInfoCard2);
                    FlashcardResult card3Result = testInfo(info3, expectedInfoCard3);
            }
        };
};







#endif
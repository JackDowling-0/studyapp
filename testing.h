#ifndef TESTING_H
#define TESTING_H

#include "flashcards.h"

class Test {

    public:

        class ParserTest{
            public:
                struct FlashcardResult {
                FlashcardResult(std::pair<int, int> idScore = {},
                                std::pair<int, std::string> questionScore = {}, 
                                std::pair<int, std::string> answerScore = {}) : idScore(idScore), questionScore(questionScore), answerScore(answerScore) {}

                std::pair<int, int> idScore;
                std::pair<int, std::string> questionScore;
                std::pair<int, std::string> answerScore;
                };

                FlashcardResult testFlashcard(Flash::Flashcard::FlashcardInfo info, Flash::Flashcard::FlashcardInfo expectedInfo){
                    FlashcardResult result;

                    if (expectedInfo.ID == info.ID){
                        result.idScore.first = 1;
                    }

                    if (expectedInfo.question == info.question){
                        result.questionScore.first = 1;
                    }

                    if (expectedInfo.answer == info.answer){
                        result.answerScore.first = 1;
                    }

                    result.idScore.second = info.ID;
                    result.questionScore.second = info.question;
                    result.answerScore.second = info.answer;

                    return result;
                }

                int testResult(Test::ParserTest::FlashcardResult test, Test::ParserTest::FlashcardResult expectedResult){
                    int testResult = 0;
                    
                    std::cout << "ID... \n";
                    //test ID
                    if (test.idScore == expectedResult.idScore){
                        testResult++;
                        std::cout << "OK \n \n";
                    } else {
                        std::cout << "No Match! \n";
                        std::cout << "  ..." << test.idScore.second << "\n";
                        std::cout << "  ..." << expectedResult.idScore.second << "\n \n";
                    }

                    //test question
                    std::cout <<"Question... \n";
                    if (test.questionScore == expectedResult.questionScore){
                        testResult++;
                        std::cout << "OK \n \n";
                    } else {
                        std::cout << "No Match! \n";
                        std::cout << "  ..." << test.questionScore.second << "\n";
                        std::cout << "  ..." << expectedResult.questionScore.second << "\n \n";
                    }

                    //test answer
                    std::cout << "Answer... \n";
                    if (test.answerScore == expectedResult.answerScore){
                        testResult++;
                        std::cout << "OK \n \n";
                    } else {
                        std::cout << "No Match! \n";
                        std::cout << "  ..." << test.answerScore.second << "\n";
                        std::cout << "  ..." << expectedResult.answerScore.second << "\n \n";
                    }

                    std::cout << "Score: " << testResult << " out of 3.";
                    std::cout << "\n--------------------------------------------------\n";
                    std::cout << "--------------------------------------------------" << std::endl;
                    return testResult;
                }

                void SingleBuildTest(){
                    Flash::FlashcardManager manager;
                    Flash::Parser parser;

                    //Create comparison objects
                    Flash::Flashcard::FlashcardInfo expectedInfoCard1 = Flash::Flashcard::FlashcardInfo(0, "This is a", "line of text");
                    Flash::Flashcard::FlashcardInfo expectedInfoCard2 = Flash::Flashcard::FlashcardInfo(1, "This is a", "line of text");
                    Flash::Flashcard::FlashcardInfo expectedInfoCard3 = Flash::Flashcard::FlashcardInfo(2, "This is a", "line of text");

                    //Set expected test results
                    FlashcardResult test1 = FlashcardResult({1, 0}, {1, "This is a"}, {1, "line of text"});
                    FlashcardResult test2 = FlashcardResult({1, 1}, {1, "This is a"}, {1, "line of text"});
                    FlashcardResult test3 = FlashcardResult({1, 2}, {1, "This is a"}, {1, "line of text"});

                    //Set of lines to test
                    std::string l1 = "This is a :line of text";
                    std::string l2 = "        This is a :line of text";
                    std::string l3 = "    This is a :   line of text     ";

                    //Create card objects to test from lines of parsing the test lines
                    Flash::Flashcard::FlashcardInfo card1 = parser.parseLine(l1).getInfo();
                    Flash::Flashcard::FlashcardInfo card2 = parser.parseLine(l2).getInfo();
                    Flash::Flashcard::FlashcardInfo card3 = parser.parseLine(l3).getInfo();

                    //Retrieve test results from card objects
                    FlashcardResult card1Result = testFlashcard(card1, expectedInfoCard1);
                    FlashcardResult card2Result = testFlashcard(card2, expectedInfoCard2);
                    FlashcardResult card3Result = testFlashcard(card3, expectedInfoCard3);

                    testResult(card1Result, test1);
                    testResult(card2Result, test2);
                    testResult(card3Result, test3);
            }
        };
};







#endif
#ifndef PARSER_H
#define PARSER_H


//class to handle parse requests and creation from long-term storage
namespace Flash{

    class Parser {
        public:

            Parser(FlashcardManager& manager) : manager(manager){}

            std::string currLine;
            FlashcardManager* ptr;

            bool isLetter(int letter){
                if (letter >= 65 && letter <= 90){
                    return true;
                } else if (letter >= 97 && letter <= 122) {
                        return true;
                    } 
                return true;
            }

            // Function to trim leading and trailing whitespace
            std::string trim(const std::string& str) {
                size_t first = str.find_first_not_of(" \t");
                if (std::string::npos == first) {
                    return str;
                }
                size_t last = str.find_last_not_of(" \t");
                return str.substr(first, (last - first + 1));
            }

            //takes in a string as input and returns a flashcard object
            Flashcard parseLine(const std::string& line, char separator = ':'){
                Flashcard card;

                // Find the position of the separator
                size_t separatorPos = line.find(separator);

                // Extract substrings and trim whitespace
                std::string leftSubstring = trim(line.substr(0, separatorPos));
                std::string rightSubstring = trim(line.substr(separatorPos + 1));

                int rawID = nextID;

                card.updateID(rawID);
                card.updateElement(leftSubstring, rightSubstring);

                return card;
            }

            //reads lines into the program, converting one line at a time
            void parseFile(const std::string& fileName){
                //open file
                std::ifstream targetFile(fileName);

                //read each line into a flashcard
                std::string rawLine;

                while (std::getline (targetFile, rawLine)){
                    //ignore empty lines
                    if (rawLine != ""){
                        manager.addFlashcard(parseLine(rawLine));
                    }
                }

                targetFile.close();
            }

        private:
            FlashcardManager& manager;

    };
}


#endif
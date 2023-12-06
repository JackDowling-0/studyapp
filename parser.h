#ifndef PARSER_H
#define PARSER_H


//class to handle parse requests and creation from long-term storage
namespace Flash{

    class Parser {
        public:

            Parser(FlashcardManager& manager) : manager(manager){}

            Parser(FlashcardManager& manager) : manager(manager){}

            std::string currLine;
            FlashcardManager* ptr;
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

            std::vector<Flashcard> parseBulkFile(const std::string& fileName){
                // create temp map
                std::vector<Flashcard> tmp;
                
                //open file
                std::ifstream targetFile(fileName);

                //read each line into a flashcard
                std::string rawLine;

                while (std::getline (targetFile, rawLine)){
                    //ignore empty lines
                    if (rawLine != ""){
                        tmp.push_back(parseLine(rawLine));
                    }
                }

                targetFile.close();
                std::ofstream ofs("dump.txt", std::ios::out | std::ios::trunc);
                ofs << "";
                ofs.close();
                
                return tmp;
            }

            void bulkUpload(){
                std::cout << "Waiting for file to close...\n";

                // Open file dialogue
                system("dump.txt");

                // Parse file and load cards into temp vector
                std::vector<Flashcard> tmp = parseBulkFile("dump.txt");

                // Output card contents and push cards onto stack
                for (const auto& card : tmp){
                    std::cout << "Question: " << card.getInfo().question << "\n";
                    std::cout << "Answer: " << card.getInfo().answer << "\n \n";
                    manager.addFlashcard(card);
                }

                // Execution completes
                std::cout << "File streaming complete. \n";
            }

        private:
            FlashcardManager& manager;

    };
}


#endif
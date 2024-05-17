#include "parser.h"
#include "flashcardmanager.h"

bool isLetter(char letter) {
    return  ((letter >= 'A') && (letter <= 'Z')) || 
            ((letter >= 'a') && (letter <= 'z'));
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
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
            tmp.push_back(parseLine(rawLine, ':'));
        }
    }

    targetFile.close();
    std::ofstream ofs("dump.txt", std::ios::out | std::ios::trunc);
    ofs << "";
    ofs.close();
    
    return tmp; 
}

Flashcard parseLine(const std::string& line, char separator = ':'){

    // Find the position of the separator
    size_t separatorPos = line.find(separator);
    if (separatorPos != line.npos){
        // Extract substrings and trim whitespace
        std::string leftSubstring = trim(line.substr(0, separatorPos));
        std::string rightSubstring = trim(line.substr(separatorPos + 1));

        Flashcard card{leftSubstring, rightSubstring};

        return card;
    } else {
        std::cout << "Please provide a question/answer pair separated by ':' \n";
        return {"", ""};
    }
}

void parsefile(const std::string& fileName){
    //open file
    std::ifstream targetFile(fileName);

    //read each line into a flashcard
    std::string rawLine;

    while (std::getline (targetFile, rawLine)){
        //ignore empty lines
        if (rawLine != ""){
            FlashcardManager::getInstance()->addFlashcard(parseLine(rawLine));
        }
    }
    targetFile.close();
}

void bulkUpload(){
    std::cout << "Waiting for file to close...\n";

    system("dump.txt");

    std::vector<Flashcard> tmp = parseBulkFile("dump.txt");

    for (const auto& card : tmp){
        std::cout << "Question: " << card.answer << "\n";
        std::cout << "Answer: " << card.answer << "\n \n";
        FlashcardManager::getInstance()->addFlashcard(card);
    }

    FlashcardManager::getInstance()->writeLibraryToStorage();
    std::cout << "File streaming complete. \n";
}